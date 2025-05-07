#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#pragma once
#include <string>
#include <algorithm>
#include <cctype>

// Trim any characters in `cutset` from front & back of s.
// By default, cuts standard whitespace.
inline std::string trim(
    const std::string& s,
    const std::string& cutset = " \t\n\r"
) {
    auto b = s.find_first_not_of(cutset);
    if (b == std::string::npos) return "";
    auto e = s.find_last_not_of(cutset);
    return s.substr(b, e - b + 1);
}

// Lower-case every character of s.
inline std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return out;
}

#endif
