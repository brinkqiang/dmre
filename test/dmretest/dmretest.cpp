#include "dmre.h"
#include <iostream>
#include <vector>

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
	std::vector<std::string> includes = {
		"#include \"dmos.h\"",
		"#include <atomic>",
		"#include <mutex>",
		"#include <mach-o/dyld.h>",
		"#include \"mach-o/dyld.h\"",
		"   #include <iostream>  ", // 添加一些额外的空格
		"#include \"path/to/file.h\"",
		"int main() { }" // 非 #include 行
	};

	for (std::string_view line : includes) {
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