#include "dmre.h"
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

std::vector<std::string> split_string(const std::string& str) {
	std::vector<std::string> result;
	std::istringstream iss(str);
	for (std::string line; std::getline(iss, line); ) {
		result.push_back(line);
	}
	return result;
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

	std::vector<std::string> include_lines = split_string(includes);

	for (const std::string& line : include_lines) {
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