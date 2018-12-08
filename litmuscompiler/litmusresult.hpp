#pragma once

#include <string>

enum class LitmusResult
{
    Maroon, // - 15 - 11
    Red, // - 10 - 6
    Pink, // - 5 - 1
    White, //	0	0
    LightBlue, //	1	5
    Blue, //	6	10
    Indigo, //	11	15
};

LitmusResult stringToLitmusResult(const std::string& str);

std::string litmusResultToString(const LitmusResult);
