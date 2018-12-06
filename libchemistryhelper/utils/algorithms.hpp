#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace LibChemistryHelper
{

namespace Utils
{
    namespace Algorithms
    {

        template <class INPUT, class RESULT>
        auto transformVector(const std::vector<INPUT> inputs, std::function<RESULT(INPUT)> fct)
        {
            std::vector<RESULT> res;
            res.reserve(inputs.size());
            std::transform(begin(inputs), end(inputs), std::back_inserter(res), fct);
            return res;
        }

    } // Algorithms

} // Utils

} // LibChemistryHelper
