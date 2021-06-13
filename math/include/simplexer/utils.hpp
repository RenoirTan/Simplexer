#ifndef SIMPLEXER_MATH_UTILS_HPP
#   define SIMPLEXER_MATH_UTILS_HPP

#   include <cctype>
#   include <cerrno>
#   include <cstdint>

namespace Simplexer::Math {

    /**
     * @brief Checks whether the current byte is a whitespace character.
     * 
     * @param unit 
     */
    bool isWhitespace(char unit) noexcept;

    /**
     * @brief Converts a character into an integer with a certain base.
     * 
     * @param unit 
     * @param base 
     * @return int32_t 
     */
    int32_t toInteger(char unit, size_t base = 10) noexcept;

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
    bool isDigit(char unit, size_t base = 10) noexcept;
}

#endif