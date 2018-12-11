#include "litmusresult.hpp"

#include "libchemistryhelper/essence.hpp"
#include "libchemistryhelper/utils/strings.hpp"

#include "numeric_range.hpp"

#include <iostream>
#include <map>
#include <set>
#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/utility/string_view.hpp>

#include <gsl/gsl_util>

namespace fs = boost::filesystem;
namespace Strings = LibChemistryHelper::Utils::Strings;

using LibChemistryHelper::Property;

namespace
{

std::string format(std::string str)
{
    str = Strings::trim(std::move(str));
    std::transform(begin(str), end(str), begin(str), &tolower);
    return str;
}

struct Constraint
{
    std::vector<std::string> essences;
    Property positive_strip;
    Property negative_strip;
    std::map<Property, LitmusResult> litmus_results;
};

using ConstraintContainer_t = std::vector<Constraint>;

auto loadResultsFile(const fs::path& file_path)
{
    std::ifstream file(file_path.string());
    if(!file) throw std::runtime_error("Unable to open " + file_path.string());
    std::vector<std::string> res;
    std::string line;
    while(std::getline(file, line))
    {
        if(!line.empty() && line.front() == '"') res.push_back(line);
    }
    return res;
}

Constraint parseLitmusResults(std::vector<std::string> essences, std::string line)
{
    auto attributes = Strings::split(line, ',');
    if(attributes.size() != 10) throw std::runtime_error("Wrong number of attributes found in : " + line);
    const auto pos_strip = LibChemistryHelper::stringToProperty(attributes[0].substr(0, 2));
    const auto neg_strip = LibChemistryHelper::stringToProperty(attributes[1].substr(0, 2));
    attributes.erase(begin(attributes), begin(attributes) + 2);
    assert(attributes.size() == 8);
    Constraint res{std::move(essences), pos_strip, neg_strip};
    for(const auto i : range(attributes.size()))
    {
        res.litmus_results[static_cast<Property>(i)] = stringToLitmusResult(format(attributes[i]));
    }
    return res;
}

/**
 * @pre line starts with an apostrophe (to begin the essence list)
 */
Constraint parseContraintLine(boost::string_view line)
{
    Expects(line.front() == '"');
    const auto end_of_essence_list = line.find('"', 1);
    if(end_of_essence_list == std::string::npos) throw std::runtime_error("Unable to parse " + line.to_string());
    const auto essences = line.substr(1, end_of_essence_list - 1);
    line = line.substr(end_of_essence_list + 2);
    auto essence_list = Strings::split(essences.to_string(), ',');
    std::transform(begin(essence_list), end(essence_list), begin(essence_list), &Strings::trim);
    if(essence_list.size() != 5)
        throw std::runtime_error("Wrong number of essences found in : " + essences.to_string());
    return parseLitmusResults(std::move(essence_list), line.to_string());
}

auto extractConstraints(const std::vector<std::string>& lines)
{
    ConstraintContainer_t res;
    res.reserve(lines.size());
    std::transform(begin(lines), end(lines), std::back_inserter(res), &parseContraintLine);
    return res;
}

auto extractUsedEssences(const ConstraintContainer_t& constraints)
{
    std::set<std::string> res;
    for(const auto& constraint : constraints)
    {
        for(const auto& essence : constraint.essences)
            res.insert(essence);
    }
    return res;
}

auto generatePossibilitiesForOneEssence(const std::string& essence_name)
{
    LibChemistryHelper::Essence::Container_t res;
    res.reserve(std::pow(7, 8));
    for(const auto ar : range<int8_t>(-3, 3))
        for(const auto as : range<int8_t>(-3, 3))
            for(const auto bi : range<int8_t>(-3, 3))
                for(const auto sa : range<int8_t>(-3, 3))
                    for(const auto so : range<int8_t>(-3, 3))
                        for(const auto sp : range<int8_t>(-3, 3))
                            for(const auto sw : range<int8_t>(-3, 3))
                                for(const auto to : range<int8_t>(-3, 3))
                                    // TODO load proper essence spirits
                                    res.push_back(LibChemistryHelper::Essence{essence_name, boost::none, "", ar, as, bi,
                                                                              sa, so, sp, sw, to});
    return res;
}

auto carthesianProduct(const std::vector<LibChemistryHelper::Essence::Container_t>& sets)
{
    std::vector<LibChemistryHelper::Essence::Container_t> res;

    return res;
}

auto generatePossibilities(const std::vector<std::string>& essence_names)
{
    std::vector<LibChemistryHelper::Essence::Container_t> possibility_per_essence(essence_names.size());
    for(const auto i : range(essence_names.size()))
    {
        possibility_per_essence[i] = generatePossibilitiesForOneEssence(essence_names[i]);
    }
    return carthesianProduct(possibility_per_essence);
}

auto doesPossibilityFitConstraint(const LibChemistryHelper::Essence::Container_t& possiblity)
{
    return [&possiblity](const Constraint& constraint) -> bool { return false; };
}

auto doesPossibilityFitConstraints(const ConstraintContainer_t& constraints)
{
    return [&constraints](const LibChemistryHelper::Essence::Container_t& possiblity) -> bool {
        return std::all_of(begin(constraints), end(constraints), doesPossibilityFitConstraint(possiblity));
    };
}

std::vector<LibChemistryHelper::Essence::Container_t>
filterPossibilities(std::vector<LibChemistryHelper::Essence::Container_t> possibilities,
                    const ConstraintContainer_t& constraints)
{
    const auto it
        = std::remove_if(begin(possibilities), end(possibilities), doesPossibilityFitConstraints(constraints));
    possibilities.erase(it, end(possibilities));
    return possibilities;
}
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "expected usage : LitmusCompiler <xls_file>" << std::endl;
        return EXIT_FAILURE;
    }
    try
    {
        const auto constraints = extractConstraints(loadResultsFile(argv[1]));
        std::cout << constraints.size() << " constraints loaded" << std::endl;
        auto essences_set = extractUsedEssences(constraints);
        std::vector<std::string> essences{begin(essences_set), end(essences_set)};
        std::cout << essences.size() << " essences found" << std::endl;
        essences.erase(begin(essences) + 10, end(essences));
        std::cout << "using only " << essences.size() << " essences" << std::endl;
        auto possibilities = generatePossibilities(essences);
        std::cout << possibilities.size() << "possibilities found" << std::endl;
        possibilities = filterPossibilities(std::move(possibilities), constraints);
        return EXIT_SUCCESS;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
