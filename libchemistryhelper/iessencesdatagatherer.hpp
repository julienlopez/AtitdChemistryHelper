#pragma once

#include "essence.hpp"

#include <vector>

namespace LibChemistryHelper
{

class IEssencesDataGatherer
{
public:
    using Container_t = std::vector<Essence>;

    virtual ~IEssencesDataGatherer() = default;

    Container_t gatherData();

protected:
    IEssencesDataGatherer() = default;

private:
    virtual Container_t impl_gatherData() = 0;
};

} // LibChemistryHelper
