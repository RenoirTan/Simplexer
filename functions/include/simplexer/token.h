#ifndef SIMPLEXER_FUNCTIONS_TOKEN_H
#   define SIMPLEXER_FUNCTIONS_TOKEN_H

#   include <stdbool.h>
#   include <stdint.h>
#   include <stdlib.h>
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
 * @brief The maximum length of a token.
 * (This is why I prefer C++ despite its intricacies)
 */
#   define SLF_TOKEN_MAXLEN 32

/**
 * @brief A structure representing a token
 * 
 * token->status:
 * -3: Internal error. That's on me.
 * -2: Token span too long
 * -1: Invalid unit
 * 0: Valid Token, but can accumulate more units
 * 1: Valid Token, but cannot accumulate more units
 * 2: Currently invalid token, but by adding more units, may become valid
 */
typedef struct SlfToken {
    SlfTokenKind token_kind;
    SlfUnit *span;
    size_t start_index;
    size_t length;
    int32_t status;
} SlfToken;

/**
 * @brief Creates a new SlfToken object.
 * 
 * @return SlfToken 
 */
SlfToken slf_token_new(void);

/**
 * @brief Initializes a SlfToken object.
 * 
 * @param token 
 * @return int32_t 
 */
int32_t slf_token_init(SlfToken *token);

/**
 * @brief Frees up the memory blocks pointed to by the pointers in a
 * SlfToken object. This does not free up the SlfToken object itself, because
 * it may have been allocated on the stack.
 * 
 * @param token 
 * @return int32_t 
 */
int32_t slf_token_destroy(SlfToken *token);

/**
 * @brief Add a unit to the span.
 * 
 * @param token 
 * @param unit 
 * @return int32_t 
 */
int32_t slf_token_add_unit(SlfToken *token, SlfUnit unit);

/**
 * @brief Reset the token to default values.
 * 
 * @param token 
 * @return int32_t 
 */
int32_t slf_token_reset(SlfToken *token);

// inline bool _slf_token_span_too_long(SlfToken *token);

/**
 * @brief Guess the TokenKind of a token if `unit` was appended to the span
 * and return the status the token should be at.
 * 
 * @param token 
 * @param unit 
 * @return int32_t 
 */
int32_t _slf_token_guess_kind(SlfToken *token, SlfUnit unit);

/**
 * @brief Checks if token->span has already been allocated on the heap.
 * 
 * Codes:
 * 0: Ok
 * -1: token is NULL
 * 1: token->span is NULL
 * 
 * @param token 
 * @return int32_t 
 */
// inline int32_t _slf_token_check_span_allocated(SlfToken *token);

/**
 * @brief Check (and change, if necessary) the value of token->length
 * depending on the value of token->span.
 * 
 * @param token 
 * @return int32_t 
 */
// inline int32_t _slf_token_check_length(SlfToken *token);

/**
 * @brief Set token->span to a 0 length C string.
 * 
 * @param token 
 * @return int32_t 
 */
int32_t _slf_token_reset_span(SlfToken *token);

/**
 * @brief Allocate memory for token->span.
 * 
 * @param token 
 * @return int32_t 
 */
int32_t _slf_token_alloc(SlfToken *token);

/*

inline bool _slf_token_is_empty(SlfToken *token);

inline bool _slf_is_eof(SlfUnit unit);

inline bool _slf_is_ascii_lower(SlfUnit unit);

inline bool _slf_is_ascii_upper(SlfUnit unit);

inline bool _slf_is_digit(SlfUnit unit);

inline bool _slf_is_underscore(SlfUnit unit);

inline bool _slf_is_potential_identifier_start(SlfUnit unit);

inline bool _slf_is_potential_identifier_unit(SlfUnit unit);

inline bool _slf_is_left_bracket(SlfUnit unit);

inline bool _slf_is_right_bracket(SlfUnit unit);

inline bool _slf_is_whitespace(SlfUnit unit);

inline bool _slf_is_comma(SlfUnit unit);

*/

#endif