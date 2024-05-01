#include <string>
#include <iostream>
#include "Token.h"
#include "StateMachine.h"
#include "Scanner.h"
#include "Debug.h"
#include "Parser.h"

void TestMachine();
void TestParser();
void TestInterpreter();
void CodeAndExecute(std::string inputFile);

int main()  {
	// TestMachine();
	// TestParser();
	TestInterpreter();
	// CodeAndExecute("code.txt");

	return 0;
}

void TestMachine() {
	ScannerClass scanner("code.txt");
	SymbolTableClass table;
	TokenType tt;
	do {
		TokenClass tc = scanner.GetNextToken();
		std::cout << "Line Number: " << scanner.getLineNumber() << " " << tc << std::endl;
		tt = tc.GetTokenType();
	} while (tt != ENDFILE_TOKEN);
}

void TestParser() {
	ScannerClass* scanner = new ScannerClass("code.txt");
	SymbolTableClass* table = new SymbolTableClass();
	ParserClass parser(scanner, table);
	StartNode * sn = parser.Start();
	if (sn) {
		std::cout << "Start Node Successfully created at Position: " << sn << std::endl;
	}
	delete sn;
}

void TestInterpreter() {
	ScannerClass* scanner = new ScannerClass("code.txt");
	SymbolTableClass* table = new SymbolTableClass();
	ParserClass parser(scanner, table);
	StartNode * sn = parser.Start();
	if (sn) {
		std::cout << "Start Node Successfully created at Position: " << sn << std::endl;
	}

	sn->Interpret();
	delete sn;
}

void CodeAndExecute(std::string inputFile)
{
	// Create scanner, symbol table, and parser objects.
	ScannerClass scanner(inputFile);
	SymbolTableClass symbolTable;
	ParserClass parser(&scanner, &symbolTable);

	// Do the parsing, which results in a parse tree.
	StartNode * root = parser.Start();

	// Create the machine code instructions from the parse tree
	InstructionsClass machineCode;
	root->Code(machineCode);
	machineCode.Finish();
	machineCode.PrintAllMachineCodes();

	// Execute the machine code instructions previously created
	machineCode.Execute();

	// cleanup recursively
	delete root;
}


