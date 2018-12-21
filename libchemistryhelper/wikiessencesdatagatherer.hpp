#pragma once

#include "libchemistryhelper/iessencesdatagatherer.hpp"

class WikiIEssencesDataGatherer : public LibChemistryHelper::IEssencesDataGatherer
{
public:
    WikiIEssencesDataGatherer() = default;

    virtual ~WikiIEssencesDataGatherer() = default;

private:
    virtual Container_t impl_gatherData() override;
};
