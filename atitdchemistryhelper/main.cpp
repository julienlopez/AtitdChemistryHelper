#include "libchemistryhelper/essencerecipefinder.hpp"

#include "wikiessencesdatagatherer.hpp"

#include <iostream>

#include <gsl/gsl_util>

namespace
{

template <class T, class CT> std::ostream& print(std::ostream& o, const boost::optional<T>& value)
{
    if(value)
        o << gsl::narrow<CT>(*value);
    else
        o << "N/A";
    return o;
}

std::vector<LibChemistryHelper::CompoundRequirement> buildRequirements(const bool do_litmus_template_runs)
{
    if(do_litmus_template_runs)
    {
        std::cout << "searching for an all-null recipe" << std::endl;
        const auto lmbd = [](const int i) { return i == 0; };
        return {{LibChemistryHelper::Property::Ar, lmbd}, {LibChemistryHelper::Property::As, lmbd},
                {LibChemistryHelper::Property::Bi, lmbd}, {LibChemistryHelper::Property::Sa, lmbd},
                {LibChemistryHelper::Property::So, lmbd}, {LibChemistryHelper::Property::Sp, lmbd},
                {LibChemistryHelper::Property::Sw, lmbd}, {LibChemistryHelper::Property::To, lmbd}};
    }
    std::vector<std::string> reqs{"Ar(--)", "As(++)"};
    std::cout << "looking for " << std::endl;
    std::copy(begin(reqs), end(reqs), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::vector<LibChemistryHelper::CompoundRequirement> requirements;
    std::transform(begin(reqs), end(reqs), std::back_inserter(requirements),
                   &LibChemistryHelper::CompoundRequirement::fromString);
    return requirements;
}
}

using LibChemistryHelper::Property;

int main(int argc, char* argv[])
{
    const bool do_litmus_template_runs = (argc == 2 && argv[1] == std::string("--template"));
    try
    {
        auto essences = WikiIEssencesDataGatherer().gatherData();
        const auto it = std::remove_if(begin(essences), end(essences), [](const LibChemistryHelper::Essence& e) {
            return !e.temperature.is_initialized();
        });
        essences.erase(it, end(essences));
        for(const auto& e : essences)
        {
            std::cout << e.material << " : ";
            print<uint8_t, int>(std::cout, e.temperature);
            std::cout << " | ";
            print<int8_t, int>(std::cout, e.properties.at(Property::Ar));
            std::cout << " | ";
            print<int8_t, int>(std::cout, e.properties.at(Property::As));
            std::cout << std::endl;
        }
        std::cout << std::endl << essences.size() << std::endl;
        LibChemistryHelper::EssenceRecipeFinder finder(essences);
        if(do_litmus_template_runs)
        {
            const auto templates = finder.findTemplates(buildRequirements(do_litmus_template_runs));
            std::cout << templates.size() << " templates found:" << std::endl;
            for(const auto& templ : templates)
            {
                std::cout << "\t " << templ[0].material << " " << templ[1].material << " " << templ[2].material << " "
                          << templ[3].material << std::endl;
            }
        }
        else
        {
            const auto recipes = finder.findRecipes(buildRequirements(do_litmus_template_runs));
            std::cout << recipes.size() << " recipes found:" << std::endl;
            for(const auto& rec : recipes)
            {
                std::cout << "\t " << rec[0].material << " " << rec[1].material << " " << rec[2].material << " "
                          << rec[3].material << " " << rec[4].material << " " << std::endl;
            }
        }
        return EXIT_SUCCESS;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
