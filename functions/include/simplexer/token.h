#ifndef SIMPLEXER_FUNCTIONS_TOKEN_H
#   define SIMPLEXER_FUNCTIONS_TOKEN_H

#   include <stdint.h>
#   include "macro.h"

#   define _SIMPLEXER_FUNCTIONS_TOKENKIND_ENUM_VALS \
    TkEof, \
    TkInvalid, \
    TkWhitespace, \
    TkIdentifier, \
    TkComma, \
    TkLeftBracket, \
    TkRightBracket

/**
 * @brief An enum classifying a token.
 */
enum TokenKind: int32_t {
    _SIMPLEXER_FUNCTIONS_TOKENKIND_ENUM_VALS
};

const char *tokenkind_as_str(enum TokenKind *tkind);

#endif