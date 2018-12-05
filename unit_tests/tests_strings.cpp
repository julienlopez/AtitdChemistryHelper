#include "libchemistryhelper/utils/strings.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Testing Utils::Strings::split with char delimiter", "[utils], [strings]")
{

    namespace Strings = LibChemistryHelper::Utils::Strings;

    SECTION("splitting a basic string")
    {
        std::string str = "A B C D";
        const auto res = Strings::split(str, ' ');
        REQUIRE(res.size() == 4);
        REQUIRE(res == std::vector<std::string>{"A", "B", "C", "D"});
    }

    SECTION("splitting a basic string with an empty element at the end")
    {
        std::string str = "A B C D ";
        const auto res = Strings::split(str, ' ');
        REQUIRE(res.size() == 5);
        REQUIRE(res == std::vector<std::string>{"A", "B", "C", "D", ""});
    }

    SECTION("splitting a basic string with an empty element at the start")
    {
        std::string str = " A B C D";
        const auto res = Strings::split(str, ' ');
        REQUIRE(res.size() == 5);
        REQUIRE(res == std::vector<std::string>{"", "A", "B", "C", "D"});
    }

    SECTION("splitting a basic string with an empty element in the middle")
    {
        std::string str = "A B  C D";
        const auto res = Strings::split(str, ' ');
        REQUIRE(res.size() == 5);
        REQUIRE(res == std::vector<std::string>{"A", "B", "", "C", "D"});
    }
}

TEST_CASE("Testing Utils::Strings::split with string delimiter", "[utils], [strings]")
{

    namespace Strings = LibChemistryHelper::Utils::Strings;

    SECTION("splitting a basic string")
    {
        std::string str = "A=!=B=!=C=!=D";
        const auto res = Strings::split(str, "=!=");
        REQUIRE(res.size() == 4);
        REQUIRE(res == std::vector<std::string>{"A", "B", "C", "D"});
    }

    SECTION("splitting a basic string with an empty element at the end")
    {
        std::string str = "A=!=B=!=C=!=D=!=";
        const auto res = Strings::split(str, "=!=");
        REQUIRE(res.size() == 5);
        REQUIRE(res == std::vector<std::string>{"A", "B", "C", "D", ""});
    }

    SECTION("splitting a basic string with an empty element at the start")
    {
        std::string str = "=!=A=!=B=!=C=!=D";
        const auto res = Strings::split(str, "=!=");
        REQUIRE(res.size() == 5);
        REQUIRE(res == std::vector<std::string>{"", "A", "B", "C", "D"});
    }

    SECTION("splitting a basic string with an empty element in the middle")
    {
        std::string str = "A=!=B=!==!=C=!=D";
        const auto res = Strings::split(str, "=!=");
        REQUIRE(res.size() == 5);
        REQUIRE(res == std::vector<std::string>{"A", "B", "", "C", "D"});
    }
}
