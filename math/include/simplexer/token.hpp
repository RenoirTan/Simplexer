/**
 * @file token.hpp
 * @author RenoirTan
 * @brief Defines functions and classes to tokenise a simple math expression.
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SIMPLEXER_MATH_TOKEN_HPP
#   define SIMPLEXER_MATH_TOKEN_HPP

#   include <cstdint>
#   include <fstream>
#   include <string>
#   include <utility>
#   include <vector>

namespace Simplexer::Math {

    /**
     * @brief An enumerator classifying a character without neighbouring
     * characters for context.
     */
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

    /**
     * @brief Get the string representation of CharKind.
     * 
     * @param ckind 
     * @return std::string 
     */
    std::string charKindAsString(CharKind ckind) noexcept;

    /**
     * @brief An enumerator classifying a group of tokens.
     */
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

    /**
     * @brief Classify a character under a CharKind.
     * 
     * @param unit 
     * @return CharKind 
     */
    CharKind getCharKind(char unit) noexcept;

    /**
     * @brief Return true if `tkind` is an operator token.
     * 
     * @param tkind 
     * @return bool
     */
    bool tokenKindIsOperator(TokenKind tkind) noexcept;

    /**
     * @brief A struct representing a token, along with other info such as
     * location of the token in the file as well as the token represented
     * as a string.
     */
    struct Token {
        /**
         * @brief The token kind the current token is grouped under.
         */
        TokenKind tokenKind;
        /**
         * @brief This token as a string.
         */
        std::string span;
        /**
         * @brief The starting index of the token in the file.
         */
        size_t startIndex;
        /**
         * @brief The end index of the token in the file. This is equal
         * to Token::startIndex + Token::span.size()
         */
        size_t endIndex;

        /**
         * @brief Construct a new Token object.
         * 
         * @param index The starting index
         */
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
         * 2: Ok, but this token is not complete yet
         * -1: Syntax Error
         * -2: Unrecognized Token Error
         * 
         * @param unit - A character
         * @return int32_t - Status code
         */
        int32_t eat(char unit);

        /**
         * @brief Check to see if this token is fully-formed.
         */
        bool isDone(void) const noexcept;

        /**
         * @brief Check if this token represents an End-of-File character.
         */
        bool isEof(void) const noexcept;
    };

    /**
     * @brief A tokenizer class which tokenises a file from an input stream.
     */
    class Tokenizer {
        public:
            /**
             * @brief Construct a new Tokenizer object. This requires that
             * you supply a pointer to a valid input file stream
             * (std::ifstream).
             * 
             * @param stream The input file stream
             */
            Tokenizer(std::ifstream *stream);

            /**
             * @brief Collect tokens from the remaining bytes in the input
             * file stream into a vector.
             * 
             * @return std::vector<Token>
             */
            std::vector<Token> getTokens(void);

            /**
             * @brief Get the next token in the stream.
             * 
             * @return Token 
             */
            Token next(void);
        private:
            /**
             * @brief The input file stream.
             */
            std::ifstream *mStream;
            /**
             * @brief The current token being built up.
             */
            Token mToken;
            /**
             * @brief The number of characters that have already been read.
             */
            size_t mIndex;
            /**
             * @brief The status code returned by the token builder.
             */
            int32_t mTokenStatus;
            /**
             * @brief A boolean value that stores whether the file stream has
             * reached the end.
             */
            bool mEofReached;
            /**
             * @brief The current byte being read from the file stream.
             */
            char mUnit;

            /**
             * @brief Consume the current byte, then reads the next byte into
             * `mUnit`. If the token builder declares that the current token
             * is unable to accept anymore bytes (i.e. mTokenStatus is 1),
             * then this tokeniser will not read the next byte, but will
             * preserve the current byte for the next token builder.
             * 
             * @return Tokenizer& This tokeniser
             */
            Tokenizer &eat(void) noexcept;

            /**
             * @brief Read the next byte in the file stream.
             * 
             * @return char The next byte
             */
            char getChar(void) noexcept;
            
            /**
             * @brief Set this tokenizer to a 'completed' state if EOF
             * reached.
             * 
             * @return Tokenizer& - This tokeniser
             */
            Tokenizer &setEofReached(void) noexcept;
    };

    /**
     * @brief Get a vector of Tokens from a input file stream
     * 
     * @param stream The input file stream
     * @return std::vector<Token> The array of tokens
     */
    std::vector<Token> tokenize(std::ifstream *stream);
}

#endif