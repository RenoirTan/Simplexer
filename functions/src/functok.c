#include <stdint.h>
#include <stdio.h>
#include <simplexer.h>


typedef struct ProgramOptions {
    char *filepath;
} ProgramOptions;


int32_t po_init(ProgramOptions *po, int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "No file path supplied.\n");
        return -1;
    }
    po->filepath = argv[1];
    return 0;
}


int32_t fprint_token(FILE *file, SlfToken *token) {
    return fprintf(
        file,
        "SlfToken "
        "{ .token_kind = %s, span = \"%s\", .start_index = %lu, "
        ".length = %lu, .status = %d }\n",
        SLF_TOKEN_KINDS[token->token_kind],
        token->span,
        token->start_index,
        token->length,
        token->status
    );
}


int run(ProgramOptions *po) {
    FILE *file = fopen(po->filepath, "r");
    SLF_NULL_RETURN(file, 1);
    SlfTokenizer tokenizer = slf_tokenizer_new();
    slf_tokenizer_set_stream(&tokenizer, file);
    SlfToken token;
    int32_t state;
    size_t reps = 0;
    do {
        state = slf_tokenizer_next(&tokenizer);
        if (state < 0) {
            fprintf(stderr, "Error: %d\n", state);
            return state;
        } else {
            token = tokenizer.token;
            fprint_token(stdout, &token);
            slf_token_destroy(&token);
        }
        reps++;
    } while (token.token_kind != SlfTkEof && reps < 30);
    fclose(file);
    return 0;
}


int main(int argc, char **argv) {
    ProgramOptions po = { 0 };
    if (po_init(&po, argc, argv)) {
        return 1;
    }
    return run(&po);
}
