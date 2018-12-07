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
            print<int8_t, int>(std::cout, e.properties.at(LibChemistryHelper::Essence::Property::Ar));
            std::cout << std::endl;
        }
        std::cout << essences.size() << std::endl;
        return EXIT_SUCCESS;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
