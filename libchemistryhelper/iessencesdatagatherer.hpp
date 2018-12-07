#pragma once

#include "essence.hpp"

namespace LibChemistryHelper
{

class IEssencesDataGatherer
{
public:
    using Container_t = Essence::Container_t;

    virtual ~IEssencesDataGatherer() = default;

    Container_t gatherData();

protected:
    IEssencesDataGatherer() = default;

private:
    virtual Container_t impl_gatherData() = 0;
};

} // LibChemistryHelper
