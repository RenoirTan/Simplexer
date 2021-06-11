#include <simplexer/token.hpp>
#include <simplexer/utils.hpp>


namespace slm = Simplexer::Math;


namespace Simplexer::Math {
    CharKind getTokenKindMonad(char unit) noexcept {
        if (isWhitespace(unit)) {
            return CharKind::Whitespace;
        } else if (isDigit(unit, 10)) {
            return CharKind::Digit;
        } else {
            switch (unit) {
                case '+':
                    return CharKind::Plus;
                case '-':
                    return CharKind::Minus;
                case '*':
                    return CharKind::Multiply;
                case '/':
                    return CharKind::Divide;
                case '^':
                    return CharKind::Exponent;
                case '(':
                    return CharKind::LeftBracket;
                case ')':
                    return CharKind::RightBracket;
                case '.':
                    return CharKind::Fullstop;
                default:
                    return CharKind::Invalid;
            }
        }
    }

    std::pair<int32_t, TokenKind> charKindToTokenKind(CharKind ckind) noexcept {
        std::pair<int32_t, TokenKind> result = std::make_pair(
            1, TokenKind::Whitespace
        );
        switch (ckind) {
            case CharKind::Invalid:
                result.first = 0;
                break;
            case CharKind::Whitespace:
                result.second = TokenKind::Whitespace;
                break;
            case CharKind::Digit:
                result.second = TokenKind::Integer;
                break;
            case CharKind::Plus:
                result.second = TokenKind::Plus;
                break;
            case CharKind::Minus:
                result.second = TokenKind::Minus;
                break;
            case CharKind::Multiply:
                result.second = TokenKind::Multiply;
                break;
            case CharKind::Divide:
                result.second = TokenKind::Divide;
                break;
            case CharKind::Exponent:
                result.second = TokenKind::Exponent;
                break;
            case CharKind::LeftBracket:
                result.second = TokenKind::LeftBracket;
                break;
            case CharKind::RightBracket:
                result.second = TokenKind::RightBracket;
                break;
            case CharKind::Fullstop:
                result.first = 2;
                break;
            default:
                break;
        }
        return result;
    }

    bool tokenKindIsOperator(TokenKind tkind) noexcept {
        return (
            tkind == TokenKind::Plus ||
            tkind == TokenKind::Minus ||
            tkind == TokenKind::Multiply ||
            tkind == TokenKind::Divide ||
            tkind == TokenKind::Exponent
        );
    }

    Token::Token(size_t index) noexcept :
        tokenKind(TokenKind::Whitespace),
        span(),
        startIndex(index),
        endIndex(index)
    {}

    bool Token::isEmpty(void) const noexcept {
        return (endIndex - startIndex) == 0;
    }

    Token::operator bool(void) const noexcept {
        return !this->isEmpty();
    }

    int32_t Token::eat(char unit) {
        CharKind ckind = getTokenKindMonad(unit);
        std::pair<int32_t, TokenKind> tkMonad = charKindToTokenKind(ckind);
        bool isNewToken = false;
        if (tkMonad.first == 0) {
            return -2;
        }
        if (this->isEmpty()) {
            if (tkMonad.first == 1) {
                tokenKind = tkMonad.second;
            } else if (tkMonad.first == 2) {
                switch (ckind) {
                    case CharKind::Fullstop:
                        return -1;
                        break;
                    default:
                        return -2;
                }
            }
        }
        switch (tokenKind) {
            case TokenKind::Whitespace:
                if (tkMonad.second != TokenKind::Whitespace) {
                    isNewToken = true;
                }
                break;
            case TokenKind::Integer:
                if (tkMonad.second == TokenKind::Integer) {
                    
                } else if (ckind == CharKind::Fullstop) {
                    tokenKind = TokenKind::Float;
                } else {
                    isNewToken = true;
                }
                break;
            case TokenKind::Float:
                if (tkMonad.second == TokenKind::Integer) {

                } else if (ckind == CharKind::Fullstop) {
                    return -1;
                } else {
                    isNewToken = true;
                }
                break;
            case TokenKind::Plus:
            case TokenKind::Minus:
            case TokenKind::Multiply:
            case TokenKind::Divide:
            case TokenKind::Exponent:
            case TokenKind::LeftBracket:
            case TokenKind::RightBracket:
            default:
                isNewToken = true;
                break;
        }
        if (isNewToken) {
            return 1;
        } else {
            span.push_back(unit);
            endIndex++;
            return 0;
        }
    }
    
    Tokenizer::Tokenizer(std::streambuf *streambuf) :
        mStream(streambuf),
        mCurrent()
    {}
}
