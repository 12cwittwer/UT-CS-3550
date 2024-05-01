#pragma once
#include <string>
#include <iostream>
#include "Debug.h"


enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IF_TOKEN, WHILE_TOKEN,
	REPEAT_TOKEN,
	// Relational Operators:
    LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	EQUAL_TOKEN, NOTEQUAL_TOKEN, AND_TOKEN, OR_TOKEN,
	// Other Operators:
    INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN,
	PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN, MOD_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
    RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, 
	BAD_TOKEN, ENDFILE_TOKEN
};

const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "IF", "WHILE",
	"REPEAT",
    "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", 
	"EQUAL", "NOTEQUAL", "AND", "OR",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
	"PLUSEQUAL", "MINUSEQUAL", "MOD",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", 
	"RCURLY",
	"IDENTIFIER", "INTEGER", 
	"BAD", "ENDFILE"
};

class TokenClass {
    private:
        TokenType mType;
        std::string mLexeme;
    public:
        TokenClass(TokenType type, const std::string& lexeme);
        TokenType GetTokenType() const;
        const std::string& GetTokenTypeName() const;
	    std::string GetLexeme() const;
	    static const std::string& GetTokenTypeName(TokenType type);
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);
