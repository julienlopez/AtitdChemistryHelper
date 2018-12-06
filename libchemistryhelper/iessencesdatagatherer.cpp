#include "iessencesdatagatherer.hpp"

namespace LibChemistryHelper
{

auto IEssencesDataGatherer::gatherData() -> Container_t
{
    return impl_gatherData();
}

} // namespace LibChemistryHelper
