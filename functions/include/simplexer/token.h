#ifndef SIMPLEXER_FUNCTIONS_TOKEN_H
#   define SIMPLEXER_FUNCTIONS_TOKEN_H

#   include <stdint.h>
#   include "macro.h"
#   include "types.h"

#   define _SLF_TOKENKIND_ENUM_VALS(APPLIER)                 \
    APPLIER(SlfTkUnknown),                                      \
    APPLIER(SlfTkEof),                                          \
    APPLIER(SlfTkInvalid),                                      \
    APPLIER(SlfTkWhitespace),                                   \
    APPLIER(SlfTkIdentifier),                                   \
    APPLIER(SlfTkComma),                                        \
    APPLIER(SlfTkLeftBracket),                                  \
    APPLIER(SlfTkRightBracket)

/**
 * @brief An enum classifying a token.
 */
typedef enum SlfTokenKind {
    _SLF_TOKENKIND_ENUM_VALS(SLF_DUMMYWRAPPER)
} SlfTokenKind;

/**
 * @brief Maps the index of a TokenKind to its corresponding string.
 */
static const char *SLF_TOKEN_KINDS[] = {
    _SLF_TOKENKIND_ENUM_VALS(SLF_STRINGIFY)
};

/**
 * @brief The minimum reserved length for Token::span
 */
static const size_t SLF_MIN_TOKEN_SPAN = 32;

/**
 * @brief How much capacity should increase at any one time
 */
static const size_t SLF_TOKEN_INCREMENT = 8;

/**
 * @brief A structure representing a token
 */
typedef struct SlfToken {
    SlfTokenKind token_kind;
    SlfUnit *span;
    size_t start_index;
    size_t length;
    size_t capacity;
} SlfToken;

SlfUnit *_slf_token_alloc_span(SlfUnit *span, size_t length);

SlfToken slf_token_new(void);

size_t slf_token_required_capacity(SlfToken *token);

#endif