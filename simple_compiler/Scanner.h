#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Token.h"
#include "StateMachine.h"



class ScannerClass {
    private:
        std::ifstream mFin;
        int mLineNumber;

    public:
        ScannerClass(std::string inputFile);
        ~ScannerClass();
        TokenClass GetNextToken();
        TokenClass PeekNextToken();
        int getLineNumber() const;
};
