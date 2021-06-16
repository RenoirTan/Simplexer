#ifndef SIMPLEXER_FUNCTION_TOKENIZER_H
#   define SIMPLEXER_FUNCTION_TOKENIZER_H

#   include <stdbool.h>
#   include <stdint.h>
#   include <stdio.h>
#   include "token.h"
#   include "types.h"
#   include "utils.h"

typedef struct SlfTokenizer {
    FILE *stream;
    SlfToken token;
    size_t index;
    SlfUnit unit;
} SlfTokenizer;

/**
 * @brief Create a new tokenizer instance.
 * 
 * @return SlfTokenizer 
 */
SlfTokenizer slf_tokenizer_new(void);

/**
 * @brief Replace the file stream in the tokenizer with a new one, returning
 * the old one in the process.
 * 
 * @param tokenizer 
 * @param stream 
 * @return FILE* 
 */
FILE *slf_tokenizer_set_stream(SlfTokenizer *tokenizer, FILE *stream);

/**
 * @brief Get the next token and return the status of the token.
 * 
 * @param tokenizer 
 * @return int32_t 
 */
int32_t slf_tokenizer_next(SlfTokenizer *tokenizer);

/**
 * @brief Reset the tokenizer but not the file.
 * 
 * @param tokenizer 
 * @return int32_t 
 */
int32_t _slf_tokenizer_reset(SlfTokenizer *tokenizer);

/**
 * @brief Feed the next byte to the token and return its status.
 * 
 * @param tokenizer 
 * @return int32_t 
 */
int32_t _slf_tokenizer_eat(SlfTokenizer *tokenizer);

/**
 * @brief Grab the next unit from the file.
 * 
 * @param tokenizer 
 * @return SlfUnit 
 */
SlfUnit _slf_tokenizer_next_unit(SlfTokenizer *tokenizer);

#endif