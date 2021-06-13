#include <cctype>
#include <cerrno>
#include <cstdint>
#include <simplexer/utils.hpp>


#ifdef SIMPLEXER_DEBUG
#   include <iostream>
#endif

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define conform(x, a, b) (max(a, min(x, b)))

namespace Simplexer::Math {

    /**
     * @brief Checks whether the current byte is a whitespace character.
     * 
     * @param unit 
     */
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

    /**
     * @brief Converts a character into an integer with a certain base.
     * 
     * @param unit 
     * @param base 
     * @return int32_t 
     */
    int32_t toInteger(char unit, size_t base) noexcept {
        if (base < 1 || base > 36) {
            return -1;
        }
        unit = (char) std::tolower(unit);
#ifdef SIMPLEXER_DEBUG
        std::cout << "toInteger -) unit: " << unit << std::endl;
        std::cout << "toInteger -) base: " << base << std::endl;
#endif
        if ('0' <= unit && unit < '0' + min(base, 10)) {
            return unit - '0';
        } else if ('a' <= unit && unit < conform(unit, 'a', 'z' + 1)) {
            return unit - 'a';
        } else {
            return -2;
        }
    }

    /**
     * @brief Checks if a character byte is a valid digit in a specified
     * number base.
     * 
     * This function uses errno.
     * If errno is 0: OK
     * If errno is 1: Base error
     * 
     * @param unit 
     * @param base
     */
    bool isDigit(char unit, size_t base) noexcept {
        int32_t res = toInteger(unit, base);
#ifdef SIMPLEXER_DEBUG
        std::cout
            << "isDigit -) res: " << res << std::endl;
#endif
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
