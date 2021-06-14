#include <string.h>
#include <simplexer/utils.h>

size_t slf_strnlen(const SlfUnit *span, size_t maxlen) {
    const char *found = memchr(span, '\0', maxlen);
    return found ? (size_t) (found - span) : maxlen;
}