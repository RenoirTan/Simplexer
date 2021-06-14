#include <stdlib.h>
#include <string.h>
#include <simplexer.h>


SlfToken slf_token_new(void) {
    SlfToken token = {
        .token_kind = SlfTkUnknown,
        .span = NULL,
        .start_index = 0,
        .length = 0
    };
    return token;
}

int32_t slf_token_init(SlfToken *token) {
    int32_t status;
    if (token == NULL) {
        return -1;
    }
    status = _slf_token_alloc(token);
    SLF_ERROR_RETURN(status);
    strcpy(token->span, "");
    return status;
}

int32_t slf_token_destroy(SlfToken *token) {
    if (token == NULL) {
        return 1;
    } else if (token->span == NULL) {
        return 2;
    } else {
        free(token->span);
    }
    return 0;
}

int32_t slf_token_set_span(SlfToken *token, SlfUnit *span) {
    int32_t status = _slf_token_check_span_allocated(token);
    SLF_ERROR_RETURN(status);
    memcpy(token->span, span, SLF_SPAN_BYTES(SLF_TOKEN_MAXLEN));
    token->span[SLF_TOKEN_MAXLEN-1] = '\0';
    status = _slf_token_check_length(token);
    return status;
}

inline int32_t _slf_token_check_span_allocated(SlfToken *token) {
    if (token == NULL) {
        return -1;
    } else if (token->span == NULL) {
        return 1;
    } else {
        return 0;
    }
}

inline int32_t _slf_token_check_length(SlfToken *token) {
    int32_t status = _slf_token_check_span_allocated(token);
    SLF_ERROR_RETURN(status);
    size_t length = slf_strnlen(token->span, SLF_TOKEN_MAXLEN);
    token->length = length;
    return status;
}

int32_t _slf_token_alloc(SlfToken *token) {
    if (token == NULL) {
        return -1;
    } else if (token->span == NULL) {
        SlfUnit *span = malloc(SLF_SPAN_BYTES(SLF_TOKEN_MAXLEN));
        if (span == NULL) {
            return -2;
        } else {
            token->span = span;
            return 0;
        }
    } else {
        SlfUnit *span = realloc(token->span, SLF_SPAN_BYTES(SLF_TOKEN_MAXLEN));
        if (span == NULL) {
            return 1;
        } else {
            token->span = span;
            return 0;
        }
    }
}
