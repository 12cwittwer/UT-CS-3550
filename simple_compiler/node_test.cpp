#include <iostream>

#include "Node.h"

int main() {
    try {
        IntegerNode* right = new IntegerNode(5);
        IntegerNode* left = new IntegerNode(3);
        PlusNode* p = new PlusNode(left, right);
        CoutStatementNode* csn1 = new CoutStatementNode(p);

        IntegerNode* in = new IntegerNode(1);
        CoutStatementNode* csn = new CoutStatementNode(in);

        StatementGroupNode* sgn = new StatementGroupNode();
        sgn->AddStatement(csn1);
        sgn->AddStatement(csn);
        BlockNode* block = new BlockNode( sgn );
        ProgramNode* pgn = new ProgramNode( block );

        // Create the root of the parse tree
        StartNode* root = new StartNode( pgn );

        delete root;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
