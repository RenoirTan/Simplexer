#include <stdlib.h>
#include <string.h>
#include <simplexer.h>


inline bool _slf_token_span_too_long(SlfToken *token) {
    return (token->length + 1 >= SLF_TOKEN_MAXLEN);
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
    size_t length = slf_strnlen(token->span, SLF_TOKEN_MAXLEN);
    token->length = length;
    return 0;
}


inline bool _slf_token_is_empty(SlfToken *token) {
    return token->length == 0;
}

inline bool _slf_is_eof(SlfUnit unit) {
    return unit == -1;
}

inline bool _slf_is_ascii_lower(SlfUnit unit) {
    return ('a' <= unit && unit <= 'z');
}

inline bool _slf_is_ascii_upper(SlfUnit unit) {
    return ('A' <= unit && unit <= 'Z');
}

inline bool _slf_is_digit(SlfUnit unit) {
    return ('0' <= unit && unit <= '9');
}

inline bool _slf_is_underscore(SlfUnit unit) {
    return unit == '_';
}

inline bool _slf_is_potential_identifier_start(SlfUnit unit) {
    return (
           _slf_is_ascii_lower(unit)
        || _slf_is_ascii_upper(unit)
        || _slf_is_underscore(unit)
    );
}

inline bool _slf_is_potential_identifier_unit(SlfUnit unit) {
    return (
           _slf_is_digit(unit)
        || _slf_is_potential_identifier_start(unit)
    );
}

inline bool _slf_is_left_bracket(SlfUnit unit) {
    return unit == '(';
}

inline bool _slf_is_right_bracket(SlfUnit unit) {
    return unit == ')';
}

inline bool _slf_is_whitespace(SlfUnit unit) {
    switch (unit) {
        case ' ':
        case '\r':
        case '\n':
        case '\t':
        case '\f':
            return true;
        default:
            return false;
    }
}

inline bool _slf_is_comma(SlfUnit unit) {
    return unit == ',';
}


SlfToken slf_token_new(void) {
    SlfToken token = {
        .token_kind = SlfTkUnknown,
        .span = NULL,
        .start_index = 0,
        .length = 0,
        .status = 2
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
    _slf_token_reset_span(token);
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

int32_t slf_token_add_unit(SlfToken *token, SlfUnit unit) {
    int32_t status = _slf_token_check_span_allocated(token);
    SLF_ERROR_RETURN(status);
    if (_slf_token_span_too_long(token)) {
        token->status = -2;
        return 2;
    } else {
        int32_t status = _slf_token_guess_kind(token, unit);
        if (status >= 0 && status != 1) {
            token->span[token->length++] = unit;
            token->span[token->length] = '\0';
        }
        token->status = status;
        return status;
    }
}

int32_t slf_token_reset(SlfToken *token) {
    int32_t status = _slf_token_check_span_allocated(token);
    SLF_ERROR_RETURN(status);
    return _slf_token_reset_span(token);
}

int32_t _slf_token_guess_kind(SlfToken *token, SlfUnit unit) {
    if (token->status < 0) {
        return token->status;
    }
    if (_slf_token_span_too_long(token)) {
        return -1;
    } else if (_slf_token_is_empty(token)) {
        if (_slf_is_eof(unit)) {
            token->token_kind = SlfTkEof;
        } else if (_slf_is_whitespace(unit)) {
            token->token_kind = SlfTkWhitespace;
        } else if (_slf_is_comma(unit)) {
            token->token_kind = SlfTkComma;
        } else if (_slf_is_left_bracket(unit)) {
            token->token_kind = SlfTkLeftBracket;
        } else if (_slf_is_right_bracket(unit)) {
            token->token_kind = SlfTkRightBracket;
        } else if (_slf_is_potential_identifier_start(unit)) {
            token->token_kind = SlfTkIdentifier;
        } else {
            return -1;
        }
        return 0;
    } else {
        if (token->token_kind == SlfTkWhitespace) {
            return !_slf_is_whitespace(unit);
        } else if (token->token_kind == SlfTkIdentifier) {
            return !_slf_is_potential_identifier_unit(unit);
        } else {
            return 1;
        }
    }
    return token->status;
}

int32_t _slf_token_reset_span(SlfToken *token) {
    strcpy(token->span, "");
    token->length = 0;
    return 0;
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
