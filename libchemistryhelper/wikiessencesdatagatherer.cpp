#include "wikiessencesdatagatherer.hpp"

#include "libchemistryhelper/utils/algorithms.hpp"
#include "libchemistryhelper/utils/strings.hpp"

#include <gsl/gsl_assert>
#include <gsl/gsl_util>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace
{

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

namespace net = boost::asio;
namespace ssl = net::ssl;

std::string fetchEssencesDataSSL()
{
    auto const host = "atitd.wiki";
    auto const port = "443";
    auto const target = "/tale8/Essences";
    const int version = 11;

    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::sslv23_client};

    tcp::resolver resolver{ioc};
    ssl::stream<tcp::socket> stream{ioc, ctx};

    if(!SSL_set_tlsext_host_name(stream.native_handle(), host))
    {
        boost::system::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
        throw boost::system::system_error{ec};
    }

    auto const results = resolver.resolve(host, port);
    boost::asio::connect(stream.next_layer(), results.begin(), results.end());
    stream.handshake(ssl::stream_base::client);

    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);
    boost::beast::flat_buffer buffer;

    http::response<http::dynamic_body> res;
    http::read(stream, buffer, res);

    return boost::beast::buffers_to_string(res.body().data());
}

boost::optional<int8_t> stoi8(const std::string& str)
{
    if(str.empty()) return boost::none;
    try
    {
        return gsl::narrow<int8_t>(stoi(str));
    }
    catch(...)
    {
        return boost::none;
    }
}

boost::optional<uint8_t> stoui8(const std::string& str)
{
    if(str.empty()) return boost::none;
    try
    {
        return gsl::narrow<int8_t>(stoul(str));
    }
    catch(...)
    {
        return boost::none;
    }
}

LibChemistryHelper::Essence parseEssenceLine(std::string str)
{
    Expects(LibChemistryHelper::Utils::Strings::beginsWith(str, "<td>"));
    Expects(LibChemistryHelper::Utils::Strings::endsWith(str, "</td>"));
    str = str.substr(4, str.size() - 4 - 5);
    auto res = LibChemistryHelper::Utils::Strings::split(str, "</td><td");
    for(auto& r : res)
    {
        const auto pos = r.find('>');
        if(pos != std::string::npos) r = r.substr(pos + 1);
    }
    assert(res.size() == 11);
    return {res[0],        stoui8(res[1]), res[2],        stoi8(res[3]), stoi8(res[4]), stoi8(res[5]),
            stoi8(res[6]), stoi8(res[7]),  stoi8(res[8]), stoi8(res[9]), stoi8(res[10])};
}

std::string isolateEssencesTable(std::string html)
{
    auto begin_pos = html.find("id=\"Essences\"");
    if(begin_pos == std::string::npos) throw std::runtime_error("nop");
    html = html.substr(begin_pos);
    begin_pos = html.find("<tbody>");
    if(begin_pos == std::string::npos) throw std::runtime_error("nop");
    html = html.substr(begin_pos + 7);
    const auto end_pos = html.find("</table>");
    if(end_pos == std::string::npos) throw std::runtime_error("nop");
    html = html.substr(0, end_pos - 8);
    Ensures(LibChemistryHelper::Utils::Strings::beginsWith(html, "<tr>"));
    Ensures(LibChemistryHelper::Utils::Strings::endsWith(html, "</tr>"));
    return html;
}

std::vector<std::string> splitHtmlTableLines(std::string html)
{
    Expects(LibChemistryHelper::Utils::Strings::beginsWith(html, "<tr>"));
    Expects(LibChemistryHelper::Utils::Strings::endsWith(html, "</tr>"));
    html = html.substr(4, html.size() - 4 - 5);
    auto res = LibChemistryHelper::Utils::Strings::split(html, "</tr><tr");
    for(auto& l : res)
    {
        const auto p = l.find("<td");
        if(p == std::string::npos) continue;
        l = l.substr(p);
    }
    return res;
}

auto parse(std::string html)
{
    html.erase(std::remove(begin(html), end(html), '\n'), end(html));
    html = isolateEssencesTable(std::move(html));
    auto lines = splitHtmlTableLines(std::move(html));
    lines.erase(begin(lines)); // removing header
    return LibChemistryHelper::Utils::Algorithms::transformVector<std::string, LibChemistryHelper::Essence>(
        lines, &parseEssenceLine);
}
}

auto WikiIEssencesDataGatherer::impl_gatherData() -> Container_t
{
    return parse(fetchEssencesDataSSL());
}
