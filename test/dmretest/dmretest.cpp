#include "dmre.h"
#include "dmstrtk.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

static constexpr auto pattern = ctll::fixed_string
{
	R"(^\s*#include\s*((?:<)(?<PATH>.*?)(?:>)|(?:")(?<PATH>.*?)(?:")))"
};

constexpr auto match(std::string_view sv) noexcept
{
	return ctre::match<pattern>(sv);
}

int main(int argc, char* argv[])
{
	std::string includes = R"(#include "dmos.h"
#include <atomic>
#include <mutex>
#include <mach-o/dyld.h>
#include "mach-o/dyld.h"
   #include <iostream>  
#include "path/to/file.h"
int main() { })";

	std::vector<std::string> include_lines;
	strtk::parse(includes, "\n", include_lines);

	for (auto& line : include_lines) {
		auto f = ctre::search<pattern>(line);
		if (f) {
			// Correctly use the id for the capture group
			std::cout << "Matched: " << f.get<1>().to_string() << std::endl;
		}
		else {
			std::cout << "No match for: " << line << std::endl;
		}
	}
	return 0;
}