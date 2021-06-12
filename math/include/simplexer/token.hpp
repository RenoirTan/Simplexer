#ifndef SIMPLEXER_MATH_TOKEN_HPP
#   define SIMPLEXER_MATH_TOKEN_HPP

#   include <cstdint>
#   include <fstream>
#   include <string>
#   include <utility>
#   include <vector>

namespace Simplexer::Math {
    enum class CharKind {
        Eof,
        Invalid,
        Whitespace,
        Digit,
        Plus,
        Minus,
        Multiply,
        Divide,
        Exponent,
        LeftBracket,
        RightBracket,
        Fullstop,
    };

    enum class TokenKind {
        Eof,
        Whitespace,
        Integer,
        Float,
        Plus,
        Minus,
        Multiply,
        Divide,
        Exponent,
        LeftBracket,
        RightBracket
    };

    /**
     * @brief Guess the kind of token from a CharKind. This CharKind is an
     * internal representation of 1 character from an istream, and so
     * does not have access to other characters within the stream.
     * 
     * result.first:
     * 0: Invalid character
     * 1: Ok, character with TokenKind found!
     * 2: Ok, but TokenKind cannot be guessed.
     * 
     * @param ckind 
     * @return std::pair<int32_t, TokenKind> - result
     */
    std::pair<int32_t, TokenKind> charKindToTokenKind(CharKind ckind) noexcept;

    CharKind getTokenKindMonad(char unit) noexcept;

    bool tokenKindIsOperator(TokenKind tkind) noexcept;

    struct Token {
        TokenKind tokenKind;
        std::string span;
        size_t startIndex;
        size_t endIndex;

        Token(size_t index = 0) noexcept;
        Token(const Token &other) = default;
        Token(Token &&other) = default;
        Token &operator=(const Token &other) = default;
        Token &operator=(Token &&other) = default;

        /**
         * @brief See if span is empty or not.
         * 
         * @return bool
         */
        bool isEmpty(void) const noexcept;

        /**
         * @brief See if the length of span is at least 1.
         * 
         * @return bool
         */
        operator bool() const noexcept;

        /**
         * @brief Eat a character and return a status code
         * 
         * 0: OK, can continue eating
         * 1: OK, but this token is done
         * -1: Syntax Error
         * -2: Unrecognized Token Error
         * 
         * @param unit - A character
         * @return int32_t - Status code
         */
        int32_t eat(char unit);

        bool isDone(void) const noexcept;

        bool isEof(void) const noexcept;
    };

    class Tokenizer {
        public:
            Tokenizer(std::ifstream *stream);

            std::vector<Token> getTokens(void);
            Token next(void);
        private:
            std::ifstream *mStream;
            Token mToken;
            size_t mIndex;
            int32_t mTokenStatus;
            bool mEofReached;
            char mUnit;

            Tokenizer &eat(void) noexcept;

            char getChar(void) noexcept;
            
            /**
             * @brief Set this tokenizer to a 'completed' state if EOF
             * reached.
             * 
             * @return Tokenizer& - this tokenizer
             */
            Tokenizer &setEofReached(void) noexcept;
    };

    std::vector<Token> tokenize(std::ifstream *stream);
}

#endif