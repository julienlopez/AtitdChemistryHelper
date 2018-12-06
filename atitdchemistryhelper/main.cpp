#include "wikiessencesdatagatherer.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        const auto essences = WikiIEssencesDataGatherer().gatherData();
        for(const auto& e : essences)
            std::cout << e.material << " : " << (int)e.temperature << " | "
                      << (int)e.properties.at(LibChemistryHelper::Essence::Property::Ar) << std::endl;
        std::cout << essences.size() << std::endl;
		return EXIT_SUCCESS;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
