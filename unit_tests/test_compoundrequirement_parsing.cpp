#include "catch2/catch.hpp"

#include "libchemistryhelper/compoundrequirement.hpp"

#include "numeric_range.hpp"

using LibChemistryHelper::CompoundRequirement;
using LibChemistryHelper::Property;

namespace
{
bool testLamba(const CompoundRequirement::TestCallback_t& lambda, const int threshold)
{
    for(const auto i : range(-16, 16))
    {
        if(threshold < 0)
        {
            if(i <= threshold && !lambda(i)) return false;
            if(i > threshold && lambda(i)) return false;
        }
        else
        {
            if(i >= threshold && !lambda(i)) return false;
            if(i < threshold && lambda(i)) return false;
        }
    }
    return true;
}

bool testRequirement(const CompoundRequirement& req, const Property prop, const int threshold)
{
    return prop == req.prop && testLamba(req.test, threshold);
}
}

TEST_CASE("Testing CompoundRequirement parsing")
{

    SECTION("Ar (+++++)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("Ar (+++++)"), Property::Ar, 13));
        CHECK(testRequirement(CompoundRequirement::fromString("Aromatic (+++++)"), Property::Ar, 13));
    }

    SECTION("As (++++)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("As (++++)"), Property::As, 10));
        CHECK(testRequirement(CompoundRequirement::fromString("Astringent  (++++)"), Property::As, 10));
    }

    SECTION("Bi (+++)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("Bi (+++)"), Property::Bi, 7));
        CHECK(testRequirement(CompoundRequirement::fromString("Bitter (+++)"), Property::Bi, 7));
    }

    SECTION("Sa (++)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("Sa (++)"), Property::Sa, 4));
        CHECK(testRequirement(CompoundRequirement::fromString("Salty (++)"), Property::Sa, 4));
    }

    SECTION("So (--)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("So (--)"), Property::So, -4));
        CHECK(testRequirement(CompoundRequirement::fromString("Sour (--)"), Property::So, -4));
    }

    SECTION("Sp (---)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("Sp (---)"), Property::Sp, -7));
        CHECK(testRequirement(CompoundRequirement::fromString("Spicy (---)"), Property::Sp, -7));
    }

    SECTION("Sw (----)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("Sw (----)"), Property::Sw, -10));
        CHECK(testRequirement(CompoundRequirement::fromString("Sweet (----)"), Property::Sw, -10));
    }

    SECTION("To (-----)")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("To (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("Toxic (-----)"), Property::To, -13));
    }

    SECTION("case sensitivity")
    {
        CHECK(testRequirement(CompoundRequirement::fromString("tO (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("to (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("To (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("TO (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("Toxic (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("toxic (-----)"), Property::To, -13));
        CHECK(testRequirement(CompoundRequirement::fromString("TOXIC (-----)"), Property::To, -13));
    }
}