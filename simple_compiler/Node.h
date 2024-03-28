#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "Debug.h"
#include "Symbol.h"

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class OrNode;
class AndNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;


class Node {
    public:
        virtual ~Node();

    private:
};

class StartNode : public Node {
    public: 
        StartNode(ProgramNode* programNode);
        virtual ~StartNode();
        void Interpret();

    private: 
        ProgramNode* programNode;
};

class ProgramNode : public Node {
    public:
        ProgramNode(BlockNode* blockNode);
        virtual ~ProgramNode();
        void Interpret();
    
    private:
        BlockNode* blockNode;
};

class StatementNode : public Node {
    public:
        StatementNode();
        virtual ~StatementNode();
        virtual void Interpret();
};

class BlockNode : public StatementNode {
    public:
        BlockNode(StatementGroupNode* statementGroupNode);
        virtual ~BlockNode();
        void Interpret();

    private:
        StatementGroupNode* statementGroupNode;
};

class StatementGroupNode : public Node {
    public:
        StatementGroupNode();
        virtual ~StatementGroupNode();
        void AddStatement(StatementNode* sn);
        void Interpret();

    private:
        std::vector<StatementNode*> mStatementNodePointers;

};


class DeclarationStatementNode : public StatementNode {
    public:
        DeclarationStatementNode(IdentifierNode* idn);
        virtual ~DeclarationStatementNode();
        void Interpret();

    private:
        IdentifierNode* mIdentifierNode;
};

class AssignmentStatementNode : public StatementNode {
    public:
        AssignmentStatementNode(IdentifierNode* idn, ExpressionNode* epn);
        virtual ~AssignmentStatementNode();
        void Interpret();

    private:
        IdentifierNode* mIdentifierNode;
        ExpressionNode* mExpressionNode;

};

class CoutStatementNode : public StatementNode {
    public:
        CoutStatementNode(ExpressionNode* epn);
        virtual ~CoutStatementNode();
        void Interpret();

    private:
        ExpressionNode* mExpressionNode;
};

class IfStatementNode : public StatementNode {
    public:
        IfStatementNode(ExpressionNode* epn, StatementNode* sn);
        virtual ~IfStatementNode();
        void Interpret();

    private:
        ExpressionNode* mExpressionNode;
        StatementNode* mStatementNode;
};

class WhileStatementNode : public StatementNode {
    public:
        WhileStatementNode(ExpressionNode* epn, StatementNode* sn);
        virtual ~WhileStatementNode();
        void Interpret();

    private:
        ExpressionNode* mExpressionNode;
        StatementNode* mStatementNode;
};

class ExpressionNode {
    public:
        ExpressionNode();
        virtual ~ExpressionNode();
        virtual int Evaluate() const = 0;

    private:
};

class IntegerNode : public ExpressionNode {
    public:
        IntegerNode(int n);
        virtual ~IntegerNode();
        virtual int Evaluate() const;

    private:
        int mInteger;
};

class IdentifierNode : public ExpressionNode {
    public:
        IdentifierNode(const std::string& label, SymbolTableClass* symbolTable);
        void DeclareVariable();
        void SetValue(int v);
        int GetIndex() const;
        int Evaluate() const;

    private:
        std::string mLabel;
        SymbolTableClass* mSymbolTable;
};

class BinaryOperatorNode : public ExpressionNode {
    public:
        BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
        ~BinaryOperatorNode();

    protected:
        ExpressionNode* mLeftExpressionNode;
        ExpressionNode* mRightExpressionNode;
};

class PlusNode : public BinaryOperatorNode {
    public:
        PlusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class MinusNode : public BinaryOperatorNode {
    public:
        MinusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class TimesNode : public BinaryOperatorNode {
    public:
        TimesNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class DivideNode : public BinaryOperatorNode {
    public:
        DivideNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class OrNode : public BinaryOperatorNode {
    public:
        OrNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class AndNode : public BinaryOperatorNode {
    public:
        AndNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class LessNode : public BinaryOperatorNode {
    public:
        LessNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class LessEqualNode : public BinaryOperatorNode {
    public:
        LessEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class GreaterNode : public BinaryOperatorNode {
    public:
        GreaterNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class GreaterEqualNode : public BinaryOperatorNode {
    public:
        GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class EqualNode : public BinaryOperatorNode {
    public:
        EqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};

class NotEqualNode : public BinaryOperatorNode {
    public:
        NotEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const;
    private:
};


#endif //NODE_H