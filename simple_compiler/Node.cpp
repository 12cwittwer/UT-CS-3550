#include "Node.h"

Node::~Node() {
}

StartNode::StartNode(ProgramNode* programNode) 
:programNode(programNode) {
    MSG("Constructing Start Node");
}

StartNode::~StartNode() {
    MSG("Destructing Start Node");
    delete programNode;
}

void StartNode::Interpret() {
    MSG("Interpreting Start Node");
    programNode->Interpret();
}


ProgramNode::ProgramNode(BlockNode* blockNode)
:blockNode(blockNode) {
    MSG("Constructing Program Node");
}

ProgramNode::~ProgramNode() {
    MSG("Destructing Program Node");
    delete blockNode;
}

void ProgramNode::Interpret() {
    MSG("Interpreting Program Node");
    blockNode->Interpret();
}

BlockNode::BlockNode(StatementGroupNode* statementGroupNode) 
:statementGroupNode(statementGroupNode) {
    MSG("Constructing Block Node");
}

BlockNode::~BlockNode() {
    MSG("Destructing Block Node");
    delete statementGroupNode;
}

void BlockNode::Interpret() {
    MSG("Interpreting Block Node");
    statementGroupNode->Interpret();
}

StatementGroupNode::StatementGroupNode() {
    MSG("Constructing Statement Group Node");
}

StatementGroupNode::~StatementGroupNode() {
    MSG("Destructing Statement Group Node");
    for (unsigned int i = 0; i < mStatementNodePointers.size(); i++) {
        delete mStatementNodePointers[i];
    }
}

void StatementGroupNode::AddStatement(StatementNode* sn) {
    mStatementNodePointers.push_back(sn);
}

void StatementGroupNode::Interpret() {
    MSG("Interpreting Statement Group Node");
    for (unsigned int i = 0; i < mStatementNodePointers.size(); i++) {
        mStatementNodePointers[i]->Interpret();
    }
}

StatementNode::StatementNode() {
    MSG("Constructing Statement Node");
}

StatementNode::~StatementNode() {
    MSG("Destructing Statement Node");
}

void StatementNode::Interpret() {
    MSG("Interpreting Statement Node");
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* idn)
: mIdentifierNode(idn) {
    MSG("Constructing Declaration Statement Node");
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("Destructing Declaration Statement Node");
    delete mIdentifierNode;
}

void DeclarationStatementNode::Interpret() {
    MSG("Interpreting Declaration Statement Node");
    mIdentifierNode->DeclareVariable();
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* idn, ExpressionNode* epn) 
 : mIdentifierNode(idn), mExpressionNode(epn) {
    MSG("Constructing Assignment Statement Node");
 }

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("Destructing Assignment Statement Node");
    delete mIdentifierNode;
    delete mExpressionNode;
}

void AssignmentStatementNode::Interpret() {
    MSG("Interpreting Assignment Statement Node");
    int outcome = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(outcome);
}

CoutStatementNode::CoutStatementNode(ExpressionNode* epn) 
: mExpressionNode(epn) {
    MSG("Constructing Cout Statement Node");
}

CoutStatementNode::~CoutStatementNode() {
    MSG("Destructing Cout Statement Node");
    delete mExpressionNode;
}

void CoutStatementNode::Interpret() {
    std::cout << mExpressionNode->Evaluate() << std::endl;
}

IfStatementNode::IfStatementNode(ExpressionNode* epn, StatementNode* sn) 
: mExpressionNode(epn), mStatementNode(sn) {
    MSG("Constructing IF Statement Node");
}

IfStatementNode::~IfStatementNode() {
    MSG("Destructing If Statement Node");
    delete mExpressionNode;
    delete mStatementNode;
}

void IfStatementNode::Interpret() {
    if (mExpressionNode->Evaluate() != 0) {
        mStatementNode->Interpret();
    }
}

WhileStatementNode::WhileStatementNode(ExpressionNode* epn, StatementNode* sn) 
: mExpressionNode(epn), mStatementNode(sn) {
    MSG("Constructing While Statement Node");
}

WhileStatementNode::~WhileStatementNode() {
    MSG("Desctructing While Statement Node");
    delete mExpressionNode;
    delete mStatementNode;
}

void WhileStatementNode::Interpret() {
    while (mExpressionNode->Evaluate() != 0) {
        mStatementNode->Interpret();
    }
}

ExpressionNode::ExpressionNode() {
    MSG("Constructing Expression Node");
}

ExpressionNode::~ExpressionNode() {
    MSG("Destructing Expression Node");
}


IntegerNode::IntegerNode(int n) 
:mInteger(n) {
    MSG("Constructing Integer Node");
}

IntegerNode::~IntegerNode() {
    MSG("Destructing Integer Node");
}

int IntegerNode::Evaluate() const {
    MSG("Evaluating Integer Node");
    return mInteger;
}

IdentifierNode::IdentifierNode(const std::string& label, SymbolTableClass* symbolTable) 
: mLabel(label), mSymbolTable(symbolTable) {
    MSG("Constructing Identifier Node");
}

void IdentifierNode::DeclareVariable() {
    MSG("Declaring Identifier Variable");
    mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) {
    mSymbolTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex() const {
    return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() const {
    MSG("Evaluating Identifier Node");
    return mSymbolTable->GetValue(mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right) 
:mLeftExpressionNode(left), mRightExpressionNode(right) {
    MSG("Constructing Binary Operator Node");
}

BinaryOperatorNode::~BinaryOperatorNode() {
    MSG("Destructing Binary Operator Node");
    delete mRightExpressionNode;
    delete mLeftExpressionNode;
}

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Plus Node");
}

int PlusNode::Evaluate() const {
    MSG("Evaluating Plus Node");
    return mLeftExpressionNode->Evaluate() + mRightExpressionNode->Evaluate();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Minus Node");
}

int MinusNode::Evaluate() const {
    MSG("Evaluating Minus Node");
    return mLeftExpressionNode->Evaluate() - mRightExpressionNode->Evaluate();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Times Node");
}

int TimesNode::Evaluate() const {
    MSG("Evaluating Times Node");
    return mLeftExpressionNode->Evaluate() * mRightExpressionNode->Evaluate();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Divide Node");
}

int DivideNode::Evaluate() const {
    MSG("Evaluating Divide Node");
    return mLeftExpressionNode->Evaluate() / mRightExpressionNode->Evaluate();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right) 
: BinaryOperatorNode(left, right) {
    MSG("Constructing OR Node");
}

int OrNode::Evaluate() const {
    MSG("Evaluating Or Node");
    return mLeftExpressionNode->Evaluate() || mRightExpressionNode->Evaluate() ? 1 : 0;
}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right) 
: BinaryOperatorNode(left, right) {
    MSG("Constructing AND Node");
}

int AndNode::Evaluate() const {
    MSG("Evaluating AND Node");
    return mLeftExpressionNode->Evaluate() && mRightExpressionNode->Evaluate() ? 1 : 0;
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Less Node");
}

int LessNode::Evaluate() const {
    MSG("Evaluating Less Node");
    return mLeftExpressionNode->Evaluate() < mRightExpressionNode->Evaluate() ? 1 : 0;
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Less Equal Node");
}

int LessEqualNode::Evaluate() const {
    MSG("Evaluating Less Equal Node");
    return mLeftExpressionNode->Evaluate() <= mRightExpressionNode->Evaluate() ? 1 : 0;
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Greater Node");
}

int GreaterNode::Evaluate() const {
    MSG("Evaluating Greater Node");
    return mLeftExpressionNode->Evaluate() > mRightExpressionNode->Evaluate() ? 1 : 0;
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Greater Equal Node");
}

int GreaterEqualNode::Evaluate() const {
    MSG("Evaluating Greater Equal Node");
    return mLeftExpressionNode->Evaluate() >= mRightExpressionNode->Evaluate() ? 1 : 0;
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Equal Node");
}

int EqualNode::Evaluate() const {
    MSG("Evaluating Equal Node");
    return mLeftExpressionNode->Evaluate() == mRightExpressionNode->Evaluate() ? 1 : 0;
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Not Equal Node");
}

int NotEqualNode::Evaluate() const {
    MSG("Evaluating Not Equal Node");
    return mLeftExpressionNode->Evaluate() != mRightExpressionNode->Evaluate() ? 1 : 0;
}
