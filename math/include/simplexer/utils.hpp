#ifndef SIMPLEXER_MATH_UTILS_HPP
#   define SIMPLEXER_MATH_UTILS_HPP

#   include <cctype>
#   include <cerrno>
#   include <cstdint>

#   define min(x, y) (x ? x < y : y)
#   define max(x, y) (x ? x > y : y)
#   define conform(x, a, b) (max(a, min(x, b)))

namespace Simplexer::Math {
    bool isWhitespace(char unit) noexcept {
        switch (unit) {
            case ' ':
            case '\r':
            case '\n':
            case '\t':
            case '\f':
                return true;
            default:
                return false;
        }
    }

    int32_t toInteger(char unit, size_t base = 10) noexcept {
        if (base < 1 || base > 36) {
            return -1;
        }
        errno = 0;
        unit = (char) std::tolower(unit);
        if ('0' <= unit && unit < '0' + min(base, 10)) {
            return unit - '0';
        } else if ('a' <= unit && unit < conform(unit, 'a', 'z' + 1)) {
            return unit - 'a';
        } else {
            return -2;
        }
    }

    bool isDigit(char unit, size_t base = 10) noexcept {
        int32_t res = toInteger(unit, base);
        switch (res) {
            case -1:
                errno = 1;
                break;
            default:
                errno = 0;
                break;
        }
        return (res >= 0);
    }
}

#endif