#include "essencerecipefinder.hpp"

#include <iostream>

namespace LibChemistryHelper
{

namespace
{
    auto essencesHaveNamesLowerThan()
    {
        return [](const Essence& e1, const Essence& e2) { return e1.material < e2.material; };
    }

    auto essencesHaveTheSameName()
    {
        return [](const Essence& e1, const Essence& e2) { return e1.material == e2.material; };
    }

    boost::optional<int8_t> operator+(boost::optional<int8_t> o1, boost::optional<int8_t> o2)
    {
        if(!o1 || !o2) return boost::none;
        return *o1 + *o2;
    }

    class Mix
    {
    public:
        Mix(const Essence& e1, const Essence& e2, const Essence& e3, const Essence& e4, const Essence& e5)
            : m_e1(e1)
            , m_e2(e2)
            , m_e3(e3)
            , m_e4(e4)
            , m_e5(e5)
        {
        }

        boost::optional<int8_t> value(const Property& prop) const
        {
            return m_e1.properties.at(prop) + m_e2.properties.at(prop) + m_e3.properties.at(prop)
                   + m_e4.properties.at(prop) + m_e5.properties.at(prop);
        }

    private:
        const Essence& m_e1;
        const Essence& m_e2;
        const Essence& m_e3;
        const Essence& m_e4;
        const Essence& m_e5;
    };

    template <class T> auto fitMix(const T& mix)
    {
        return [&mix](const CompoundRequirement& req) -> bool {
            const auto res = mix.value(req.prop);
            if(res) return req.test(*res);
            return false;
        };
    }

    constexpr std::size_t factorial(const std::size_t n)
    {
        if(n == 0) return 1;
        return n * factorial(n - 1);
    }

    class Template
    {
    public:
        Template(const Essence& e1, const Essence& e2, const Essence& e3, const Essence& e4)
            : m_e1(e1)
            , m_e2(e2)
            , m_e3(e3)
            , m_e4(e4)
        {
        }

        boost::optional<int8_t> value(const Property& prop) const
        {
            return m_e1.properties.at(prop) + m_e2.properties.at(prop) + m_e3.properties.at(prop)
                   + m_e4.properties.at(prop);
        }

    private:
        const Essence& m_e1;
        const Essence& m_e2;
        const Essence& m_e3;
        const Essence& m_e4;
    };
}

EssenceRecipeFinder::EssenceRecipeFinder(EssenceContainer_t essences,
                                         boost::optional<OnResultCallback_t> on_result_callback)
    : m_essences(std::move(essences))
    , m_on_result_callback(on_result_callback)
{
}

auto EssenceRecipeFinder::findRecipes(const CompoundRequirementContainer_t& requirements) const -> ResultContainer_t
{
    ResultContainer_t res;
    const auto valid_essences = findValidEssences(requirements);
    std::cout << valid_essences.size() << " valid essences found:" << std::endl;
    if(valid_essences.size() > 20)
        std::cout << "accounting for too many possibilities to count" << std::endl;
    else
        std::cout << "accounting for " << factorial(valid_essences.size()) << " possibilities" << std::endl;
    for(auto it1 = begin(valid_essences); it1 != end(valid_essences); ++it1)
        for(auto it2 = it1 + 1; it2 != end(valid_essences); ++it2)
            for(auto it3 = it2 + 1; it3 != end(valid_essences); ++it3)
                for(auto it4 = it3 + 1; it4 != end(valid_essences); ++it4)
                    for(auto it5 = it4 + 1; it5 != end(valid_essences); ++it5)
                    {
                        const Mix mix(*it1, *it2, *it3, *it4, *it5);
                        if(std::all_of(begin(requirements), end(requirements), fitMix(mix)))
                        {
                            Result_t recipe{*it1, *it2, *it3, *it4, *it5};
                            if(m_on_result_callback) (*m_on_result_callback)(recipe);
                            res.push_back(recipe);
                        }
                    }
    return res;
}

auto EssenceRecipeFinder::findTemplates(const CompoundRequirementContainer_t& requirements) const -> TemplateContainer_t
{
    TemplateContainer_t res;
    const auto valid_essences = findValidEssences(requirements);
    std::cout << valid_essences.size() << " valid essences found:" << std::endl;
    if(valid_essences.size() > 20)
        std::cout << "accounting for too many possibilities to count" << std::endl;
    else
        std::cout << "accounting for " << factorial(valid_essences.size()) << " possibilities" << std::endl;
    for(auto it1 = begin(valid_essences); it1 != end(valid_essences); ++it1)
        for(auto it2 = it1 + 1; it2 != end(valid_essences); ++it2)
            for(auto it3 = it2 + 1; it3 != end(valid_essences); ++it3)
                for(auto it4 = it3 + 1; it4 != end(valid_essences); ++it4)
                {
                    const Template mix(*it1, *it2, *it3, *it4);
                    if(std::all_of(begin(requirements), end(requirements), fitMix(mix)))
                        res.push_back({*it1, *it2, *it3, *it4});
                }
    return res;
}

auto EssenceRecipeFinder::findValidEssences(const CompoundRequirementContainer_t& requirements) const
    -> EssenceContainer_t
{
    EssenceContainer_t valid_essences;
    std::copy_if(begin(m_essences), end(m_essences), std::back_inserter(valid_essences),
                 [&requirements](const Essence& e) {
                     for(const auto& req : requirements)
                         if(!e.properties.at(req.prop)) return false;
                     return true;
                 });
    return valid_essences;
}

} // namespace LibChemistryHelper
