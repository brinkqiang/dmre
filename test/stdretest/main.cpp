#include <iostream>
#include <string>
#include <regex>

int main()
{
    // Simple regular expression matching
    std::string fnames[] = {"foo.txt", "bar.txt", "baz.dat", "zoidberg"};
    std::regex txt_regex("[a-z]+\\.txt");

    for (const auto& fname : fnames)
    {
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
    }

    // Extraction of a sub-match
    std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;

    for (const auto& fname : fnames)
    {
        if (std::regex_match(fname, base_match, base_regex))
        {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (base_match.size() == 2)
            {
                std::ssub_match base_sub_match = base_match[1];
                std::string base = base_sub_match.str();
                std::cout << fname << " has a base of " << base << '\n';
            }
        }
    }

    // Extraction of several sub-matches
    std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
    std::smatch pieces_match;

    for (const auto& fname : fnames)
    {
        if (std::regex_match(fname, pieces_match, pieces_regex))
        {
            std::cout << fname << '\n';

            for (size_t i = 0; i < pieces_match.size(); ++i)
            {
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }
        }
    }

    std::string includes[] = {R"(#include "dmos.h")",R"(#include <atomic>)",R"(#include <stdio.h>)",R"(#include <mach-o/dyld.h>)"};

    try
    {
        std::regex includes_regex(
            R"(^\s*#include\s*(?:(?:<)(?<PATH>.*?)(?:>)|(?:")(?<PATH>.*?)(?:")))");

        std::smatch includes_match;

        for (const auto& inc : includes)
        {
            if (std::regex_match(inc, includes_match, includes_regex))
            {
                std::cout << inc << '\n';

                for (size_t i = 0; i < includes_match.size(); ++i)
                {
                    std::ssub_match sub_match = includes_match[i];
                    std::string piece = sub_match.str();
                    std::cout << "  submatch " << i << ": " << piece << '\n';
                }
            }
        }
    }
    catch (std::regex_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}