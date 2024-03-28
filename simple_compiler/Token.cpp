#include "Token.h"

TokenClass::TokenClass(TokenType type, const std::string& lexeme)
: mType(type), mLexeme(lexeme) {
    if (lexeme == "void") {
        mType = TokenType::VOID_TOKEN;
    } else if (lexeme == "main") {
        mType = TokenType::MAIN_TOKEN;
    } else if (lexeme == "int") {
        mType = TokenType::INT_TOKEN;
    } else if (lexeme == "cout") {
        mType = TokenType::COUT_TOKEN;
    } else if (lexeme == "if") {
        mType = TokenType::IF_TOKEN;
    } else if (lexeme == "while") {
        mType = TokenType::WHILE_TOKEN;
    }
};

TokenType TokenClass::GetTokenType() const { 
    return mType; 
};

const std::string& TokenClass::GetTokenTypeName() const {
    return gTokenTypeNames[mType];
};

std::string TokenClass::GetLexeme() const { 
    return mLexeme; 
}

const std::string& TokenClass::GetTokenTypeName(TokenType type) { 
    return gTokenTypeNames[type]; 
};

std::ostream &operator<<(std::ostream &out, const TokenClass &tc) {
    out << "Type: " << tc.GetTokenType() << ", Name: " << tc.GetTokenTypeName() << ", Lexeme: " << tc.GetLexeme();
    return out;
}

