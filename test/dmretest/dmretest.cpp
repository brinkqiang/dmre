
#include "dmre.h"

static constexpr auto pattern = ctll::fixed_string
{
    R"(^\s*#include\s*(?:(?:<)(?<PATH>.*?)(?:>)|(?:")(?<PATH>.*?)(?:")))"
};

constexpr auto match(std::string_view sv) noexcept
{
    return ctre::match<pattern>(sv);
}

int main( int argc, char* argv[] )
{
    auto f = match(R"(#include "dmos.h"
#include <atomic>
#include <mutex>
#include <mach-o/dyld.h>
#include <mach-o/dyld.h>
)");
    return 0;
}
