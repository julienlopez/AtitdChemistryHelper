#include "litmusresult.hpp"

#include <algorithm>
#include <map>

namespace
{
using LitmusResultLabels = std::map<LitmusResult, std::string>;

LitmusResultLabels labels()
{
    return {{LitmusResult::Maroon, "maroon"},
            {LitmusResult::Red, "red"},
            {LitmusResult::Pink, "pink"},
            {LitmusResult::White, "white"},
            {LitmusResult::LightBlue, "light blue"},
            {LitmusResult::Blue, "blue"},
            {LitmusResult::Indigo, "indigo"}};
}
}

LitmusResult stringToLitmusResult(const std::string& str)
{
    const auto lab = labels();
    const auto it = std::find_if(begin(lab), end(lab),
                                 [&str](const LitmusResultLabels::value_type& p) { return p.second == str; });
    return it->first;
}

std::string litmusResultToString(const LitmusResult prop)
{
    return labels().at(prop);
}
