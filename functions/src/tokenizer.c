#include <simplexer.h>

#ifdef SIMPLEXER_DEBUG
#   include <stdio.h>
#endif


SlfTokenizer slf_tokenizer_new(void) {
    SlfToken token = slf_token_new();
    slf_token_init(&token);
    SlfTokenizer tokenizer = {
        .stream = NULL,
        .token = token,
        .index = 0,
        .unit = '\0'
    };
    return tokenizer;
}

FILE *slf_tokenizer_set_stream(SlfTokenizer *tokenizer, FILE *stream) {
    SLF_NULL_RETURN(tokenizer, NULL);
    FILE *old_file = tokenizer->stream;
    tokenizer->stream = stream;
    _slf_tokenizer_reset(tokenizer);
    return old_file;
}

int32_t slf_tokenizer_next(SlfTokenizer *tokenizer) {
    int32_t status;
    do {
        status = _slf_tokenizer_eat(tokenizer);
        switch (status) {
            case 0:
            case 2:
                continue;
            case 1:
                break;
            case -1:
            case -2:
            case -3:
                return status;
            default:
                return -3;
        }
    } while (tokenizer->token.status != 1);
    return status;
}

int32_t _slf_tokenizer_reset(SlfTokenizer *tokenizer) {
    slf_token_reset(&tokenizer->token);
    tokenizer->index = 0;
    return 0;
}

int32_t _slf_tokenizer_eat(SlfTokenizer *tokenizer) {
    switch (tokenizer->token.status) {
        case -1:
        case -2:
        case -3:
            return tokenizer->token.status;
        case 0:
        case 2:
            _slf_tokenizer_next_unit(tokenizer);
            slf_token_add_unit(&tokenizer->token, tokenizer->unit);
            break;
        case 1: {
            SlfToken token = slf_token_new();
            slf_token_init(&token);
            token.start_index = tokenizer->index;
            token.status = 2;
            tokenizer->token = token;
            slf_token_add_unit(&tokenizer->token, tokenizer->unit);
            break;
        }
        default:
            return -3;
    }
#ifdef SIMPLEXER_DEBUG
    printf("current char: %c\n", tokenizer->unit);
    printf("current index: %lu\n", tokenizer->index);
    printf("tokenizer status: %d\n", tokenizer->token.status);
#endif
    return tokenizer->token.status;
}

SlfUnit _slf_tokenizer_next_unit(SlfTokenizer *tokenizer) {
    tokenizer->unit = fgetc(tokenizer->stream);
    tokenizer->index++;
    return tokenizer->unit;
}
