#ifndef SIMPLEXER_MATH_TOKEN_HPP
#   define SIMPLEXER_MATH_TOKEN_HPP

#   include <istream>
#   include <string>
#   include <utility>
#   include <cstdint>

namespace Simplexer::Math {
    enum class CharKind {
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
        bool isEmpty(void) const noexcept;
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
    };

    class Tokenizer {
        public:
            Tokenizer(std::streambuf *streambuf);
            Token next(void);
        private:
            std::istream mStream;
            Token mCurrent;
            size_t mIndex;

            Tokenizer &eat(void);
    };
}

#endif