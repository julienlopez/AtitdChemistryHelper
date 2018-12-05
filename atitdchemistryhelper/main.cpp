#include "libchemistryhelper/strings.hpp"

#include <iostream>

#include <gsl/gsl_assert>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

namespace net = boost::asio; // from <boost/asio.hpp>
namespace ssl = net::ssl; // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp; // from <boost/asio/ip/tcp.hpp>

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

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);
    boost::beast::flat_buffer buffer;

    http::response<http::dynamic_body> res;
    http::read(stream, buffer, res);

    // std::cout << res << std::endl;
    // std::string str;

    const auto str = boost::beast::buffers_to_string(res.body().data());
    /*
    // Gracefully close the stream
    boost::system::error_code ec;
    stream.shutdown(ec);
    if(ec == boost::asio::error::eof)
        ec.assign(0, ec.category());
    if(ec) throw boost::system::system_error{ec};
    */

    return str;
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

void parse(std::string html)
{
    html = isolateEssencesTable(std::move(html));
    html = html.substr(4, html.size() - 4 - 5);
    std::cout << html << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        parse(fetchEssencesDataSSL());
        return EXIT_SUCCESS;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
