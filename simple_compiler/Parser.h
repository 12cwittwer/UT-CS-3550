#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include "Debug.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"

class ParserClass {
    private:
        ScannerClass* mScannerClass;
        SymbolTableClass* mSymbolTableClass;
        ProgramNode * Program();
        BlockNode * Block();
        StatementGroupNode * StatementGroup();
        StatementNode * Statement();
        DeclarationStatementNode * DeclarationStatement();
        AssignmentStatementNode * AssignmentStatement(); 
        CoutStatementNode * CoutStatement();
        IfStatementNode * IfStatement();
        WhileStatementNode * WhileStatement();
        RepeatStatementNode * RepeatStatement();
        IdentifierNode * Identifier();
        ExpressionNode * Expression();
        ExpressionNode * Or();
        ExpressionNode * And();
        ExpressionNode * Relational();
        ExpressionNode * PlusMinus();
        ExpressionNode * TimesDivide();
        ExpressionNode * Factor();
        IntegerNode * Integer();
    public:
        ParserClass(ScannerClass* sc, SymbolTableClass* stc); 
        TokenClass Match(TokenType expectedType);
        StartNode * Start();
};