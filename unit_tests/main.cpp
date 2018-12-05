#include <catch2/internal/catch_interfaces_reporter.h>
#include <catch2/internal/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_session.h>
#include <catch2/reporters/catch_reporter_console.h>
#include <catch2/reporters/catch_reporter_junit.h>

namespace Catch
{

CATCH_REGISTER_REPORTER("console", ConsoleReporter)
CATCH_REGISTER_REPORTER("junit", JunitReporter)
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}
