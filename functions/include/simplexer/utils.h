#ifndef SIMPLEXER_FUNCTIONS_UTILS_H
#   define SIMPLEXER_FUNCTIONS_UTILS_H

#   include <stdint.h>
#   include "types.h"

/**
 * @brief Custom strnlen because string.h doesn't implement it.
 * Stolen from https://stackoverflow.com/questions/66346502/which-is-most-standard-strnlen-or-strnlen-s
 * 
 * @param span 
 * @param maxlen 
 * @return size_t 
 */
size_t slf_strnlen(const SlfUnit *span, size_t maxlen);

#endif