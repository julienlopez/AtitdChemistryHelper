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
}

using LibChemistryHelper::Property;

int main(int argc, char* argv[])
{
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
        std::cout << "looking for Ar(--) As(++)" << std::endl;
        LibChemistryHelper::EssenceRecipeFinder finder(essences);
        const auto recipes = finder.findRecipes({LibChemistryHelper::CompoundRequirement::fromString("Ar(--)"),
                                                 LibChemistryHelper::CompoundRequirement::fromString("As(++)")});
        std::cout << recipes.size() << " recipes found:" << std::endl;
        for(const auto& rec : recipes)
        {
            std::cout << "\t " << rec[0].material << " " << rec[1].material << " " << rec[2].material << " "
                      << rec[3].material << " " << rec[4].material << " " << std::endl;
        }
        return EXIT_SUCCESS;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
