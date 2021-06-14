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
 * @brief The maximum length of a token.
 * (This is why I prefer C++ despite its intricacies)
 */
#   define SLF_TOKEN_MAXLEN 32

/**
 * @brief A structure representing a token
 */
typedef struct SlfToken {
    SlfTokenKind token_kind;
    SlfUnit *span;
    size_t start_index;
    size_t length;
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
 * @brief Set token->span to a predetermined value. If `span` exceeds
 * `SLF_TOKEN_MAXLEN`, it will be cut off prematurely by the sentinel
 * value used to terminate C strings (i.e. '\0').
 * 
 * @param token 
 * @param span 
 * @return int32_t 
 */
int32_t slf_token_set_span(SlfToken *token, SlfUnit *span);

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
inline int32_t _slf_token_check_span_allocated(SlfToken *token);

/**
 * @brief Check (and change, if necessary) the value of token->length
 * depending on the value of token->span.
 * 
 * @param token 
 * @return int32_t 
 */
inline int32_t _slf_token_check_length(SlfToken *token);

/**
 * @brief Allocate memory for token->span.
 * 
 * @param token 
 * @return int32_t 
 */
int32_t _slf_token_alloc(SlfToken *token);

#endif