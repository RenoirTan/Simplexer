#include <stdlib.h>
#include <simplexer.h>

SlfUnit *_slf_token_alloc_span(SlfUnit *span, size_t length) {
    length = max(length, SLF_MIN_TOKEN_SPAN);
    if (span == NULL) {
        return malloc(length * sizeof(SlfUnit));
    } else {
        return realloc(span, length * sizeof(SlfUnit));
    }
}

SlfToken slf_token_new(void) {
    SlfToken token = {
        .token_kind = SlfTkUnknown,
        .span = NULL,
        .start_index = 0,
        .length = 0,
        .capacity = 0
    };
    return token;
}

size_t slf_token_required_capacity(SlfToken *token) {
    if (token->length < SLF_MIN_TOKEN_SPAN) {
        return SLF_MIN_TOKEN_SPAN;
    } else {
        size_t blocks = (token->length - SLF_MIN_TOKEN_SPAN)
            / SLF_TOKEN_INCREMENT;
        
    }
}
