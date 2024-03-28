#include "Scanner.h"

ScannerClass::ScannerClass(std::string inputFileName) 
:mLineNumber(1)
{
    mFin.open(inputFileName.c_str(), std::ios::binary);

    //Error message if nothing is read
    if (!mFin) {
		std::cerr << "Error opening input file " << inputFileName;
		std::exit(1);
	}

}

ScannerClass::~ScannerClass() {
    mFin.close();
}

TokenClass ScannerClass::GetNextToken() {
        StateMachineClass stateMachine;
        std::string lexeme;
        MachineState currentState;
        TokenType previousTokenType;

        do {
            char c = mFin.get();
            lexeme += c;
            if (lexeme == "\n") {
                mLineNumber++;
            }
            currentState = stateMachine.UpdateState(c, previousTokenType);
            if (currentState == START_STATE || currentState == ENDFILE_STATE || currentState == LINECOMMENT_STATE || currentState == BLOCKCOMMENT1_STATE || currentState == BLOCKCOMMENT2_STATE) {
                lexeme = "";
            }
        } while (currentState != CANTMOVE_STATE);

        if (previousTokenType == BAD_TOKEN) {
            std::cerr << "Error. BAD_TOKEN from lexeme " << lexeme;
            std::exit(1);
        }

        // Remove the last character (which caused the CANT_MOVE state) from lexeme
        if (!lexeme.empty()) {
            lexeme.pop_back();
        }

        // Unget the last character unless it's a newline, which was counted
        if (lexeme.back() != '\n') {
            mFin.unget();
        }

        TokenClass tc(previousTokenType, lexeme);
        return tc;
    }

TokenClass ScannerClass::PeekNextToken() {
    std::streampos position = mFin.tellg();
    // int line_position = mLineNumber;
    TokenClass next_token = GetNextToken();
    if (!mFin) {
        mFin.clear();
    }
    mFin.seekg(position);
    return next_token;
}

int ScannerClass::getLineNumber() const {
    return mLineNumber;
}
