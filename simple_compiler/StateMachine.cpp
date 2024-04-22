#include "StateMachine.h"

StateMachineClass::StateMachineClass()
: mCurrentState(MachineState::START_STATE) {
    for(int i=0; i<LAST_STATE; i++) {
        for(int j=0; j<LAST_CHAR; j++) {
            mLegalMoves[i][j] = MachineState::CANTMOVE_STATE;
        }
    }

    //Make all moves inside Comments legal
    for (int i = 0; i < LAST_CHAR; i++) {
        mLegalMoves[LINECOMMENT_STATE][i] = LINECOMMENT_STATE;
        mLegalMoves[BLOCKCOMMENT1_STATE][i] = BLOCKCOMMENT1_STATE;
        mLegalMoves[BLOCKCOMMENT2_STATE][i] = BLOCKCOMMENT1_STATE;
    }

    //
    //Refining Legal Moves for Comments
    //
    //Line Comments
    mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
    mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;
    mLegalMoves[LINECOMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
    //Block Comments
    mLegalMoves[DIVIDE_STATE][MULTIPLY_CHAR] = BLOCKCOMMENT1_STATE;
    mLegalMoves[BLOCKCOMMENT1_STATE][MULTIPLY_CHAR] = BLOCKCOMMENT2_STATE;
    mLegalMoves[BLOCKCOMMENT2_STATE][MULTIPLY_CHAR] = BLOCKCOMMENT2_STATE;
    mLegalMoves[BLOCKCOMMENT2_STATE][DIVIDE_CHAR] = START_STATE;

    //Create all legal moves
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][UNDERSCORE_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
    mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
    mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
    mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
    mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;
    mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
    mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    mLegalMoves[START_STATE][MULTIPLY_CHAR] = MULTIPLY_STATE;
    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;
    mLegalMoves[START_STATE][BANG_CHAR] = BANG_STATE;
    mLegalMoves[BANG_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;

    // And and or states
    mLegalMoves[START_STATE][AMPERSAND_CHAR] = AND_START;
    mLegalMoves[AND_START][AMPERSAND_CHAR] = AND_END;
    mLegalMoves[START_STATE][PIPE_CHAR] = OR_START;
    mLegalMoves[OR_START][PIPE_CHAR] = OR_END; 

    // Special States
    mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUSEQUAL_STATE;
    mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MINUSEQUAL_STATE;

    //Initialize all states to correspond to BAD_TOKEN
    for (int i = 0; i < LAST_STATE; i++) {
        mCorrespondingTokenType[i] = BAD_TOKEN; 
    }

    //Connect Comment STATE's with what???

    //
    //Connect STATE's with TOKENS
    //
    mCorrespondingTokenType[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenType[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenType[ENDFILE_STATE] = ENDFILE_TOKEN;
    mCorrespondingTokenType[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenType[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenType[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenType[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenType[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenType[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenType[GREATER_STATE] = GREATER_TOKEN;
    mCorrespondingTokenType[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenType[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenType[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenType[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenType[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenType[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenType[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenType[MULTIPLY_STATE] = TIMES_TOKEN;
    mCorrespondingTokenType[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenType[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;

    //Special tokens
    mCorrespondingTokenType[MINUSEQUAL_STATE] = MINUSEQUAL_TOKEN;
    mCorrespondingTokenType[PLUSEQUAL_STATE] = PLUSEQUAL_TOKEN;

    //Connect AND and OR states with TOKENS
    mCorrespondingTokenType[AND_END] = AND_TOKEN;
    mCorrespondingTokenType[OR_END] = OR_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType &previousTokenType) {
    // convert the input character into an input character type
	CharacterType charType = BAD_CHAR;

    //Convert input into a CharacterType
    if (isdigit(currentCharacter)) {
        charType = DIGIT_CHAR;
    } else if (isalpha(currentCharacter)) {
        charType = LETTER_CHAR;
    } else if (currentCharacter == '\n') {
        charType = NEWLINE_CHAR;
    } else if (currentCharacter == '\t' || currentCharacter == ' ') {
        charType = WHITESPACE_CHAR;
    } else if (currentCharacter == '+') {
        charType = PLUS_CHAR;
    } else if (currentCharacter == '-') {
        charType = MINUS_CHAR;
    } else if (currentCharacter == '_') {
        charType = UNDERSCORE_CHAR;
    } else if (currentCharacter == '(') {
        charType = LPAREN_CHAR;
    } else if (currentCharacter == ')') {
        charType = RPAREN_CHAR;
    } else if (currentCharacter == '{') {
        charType = LCURLY_CHAR;
    } else if (currentCharacter == '}') {
        charType = RCURLY_CHAR;
    } else if (currentCharacter == '<') {
        charType = LESS_CHAR;
    } else if (currentCharacter == '>') {
        charType = GREATER_CHAR;
    } else if (currentCharacter == '=') {
        charType = EQUAL_CHAR;
    } else if (currentCharacter == EOF) {
        charType = ENDFILE_CHAR;
    } else if (currentCharacter == 10) {
        charType = NEWLINE_CHAR;
    } else if (currentCharacter == '/') {
        charType = DIVIDE_CHAR;
    } else if (currentCharacter == '*') {
        charType = MULTIPLY_CHAR;
    } else if (currentCharacter == ';') {
        charType = SEMICOLON_CHAR;
    } else if (currentCharacter == '!') {
        charType = BANG_CHAR;
    } else if (currentCharacter == '&') {
        charType = AMPERSAND_CHAR;
    } else if (currentCharacter == '|') {
        charType = PIPE_CHAR;
    }
    else {
        charType = BAD_CHAR;
    }

    //Update previous token type and current state
    previousTokenType = mCorrespondingTokenType[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];

    return mCurrentState;
}