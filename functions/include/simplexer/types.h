#ifndef SIMPLEXER_FUNCTIONS_TYPES_H
#   define SIMPLEXER_FUNCTIONS_TYPES_H

#   include <stdint.h>

/**
 * @brief The type used to represent a character in a token.
 */
typedef char SlfUnit;

#   define SLF_SPAN_BYTES(length) (length * sizeof(SlfUnit))

/**
 * @brief The type used to represented the status code of an action, such
 * as a result of a function.
 */
typedef int32_t SlfStatus;

#endif