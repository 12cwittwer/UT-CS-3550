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

void StartNode::Code(InstructionsClass &machineCode)
{
    MSG("Coding Start Node");
	programNode->Code(machineCode);
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

void ProgramNode::Code(InstructionsClass &machineCode)
{
    MSG("Coding Program Node");
	blockNode->Code(machineCode);
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

void BlockNode::Code(InstructionsClass &machineCode) {
    MSG("Coding Block Node");
    statementGroupNode->Code(machineCode);
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

void StatementGroupNode::Code(InstructionsClass &machineCode) {
    MSG("Coding Statement Group Node");
    for (unsigned int i = 0; i < mStatementNodePointers.size(); i++) {
        mStatementNodePointers[i]->Code(machineCode);
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
void DeclarationStatementNode::Code(InstructionsClass &machineCode) {
    MSG("Coding Declaration Statment Node");
    (void)machineCode;
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

void AssignmentStatementNode::Code(InstructionsClass &machineCode) {
    MSG("Coding Assignment Statement Node");
    mExpressionNode->CodeEvaluate(machineCode);
    int index = mIdentifierNode->GetIndex();
    machineCode.PopAndStore(index);
}

PlusEqualStatementNode::PlusEqualStatementNode(IdentifierNode* idn, ExpressionNode* epn) 
 : mIdentifierNode(idn), mExpressionNode(epn) {
    MSG("Constructing Plus Equal Statement Node");
 }

 PlusEqualStatementNode::~PlusEqualStatementNode() {
    MSG("Destructing Plus Equal Statement Node");
    delete mIdentifierNode;
    delete mExpressionNode;
}

void PlusEqualStatementNode::Interpret() {
    MSG("Interpreting Plus Equal Statement Node");
    int prev = mIdentifierNode->Evaluate();
    int outcome = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(prev + outcome);
}

void PlusEqualStatementNode::Code(InstructionsClass &machineCode) { // Look at book for Code()
    MSG("Coding Plus Equal Statement Node");
    int index = mIdentifierNode->GetIndex();
    machineCode.PushVariable(index);
    mExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
    machineCode.PopAndStore(index);
}

MinusEqualStatementNode::MinusEqualStatementNode(IdentifierNode* idn, ExpressionNode* epn) 
 : mIdentifierNode(idn), mExpressionNode(epn) {
    MSG("Constructing Minus Equal Statement Node");
 }

 MinusEqualStatementNode::~MinusEqualStatementNode() {
    MSG("Destructing Minus Equal Statement Node");
    delete mIdentifierNode;
    delete mExpressionNode;
}

void MinusEqualStatementNode::Interpret() {
    MSG("Interpreting Minus Equal Statement Node");
    int prev = mIdentifierNode->Evaluate();
    int outcome = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(prev - outcome);
}

void MinusEqualStatementNode::Code(InstructionsClass &machineCode) { // Look at book for Code()
    MSG("Coding Minus Equal Statement Node");
    int index = mIdentifierNode->GetIndex();
    machineCode.PushVariable(index);
    mExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
    machineCode.PopAndStore(index);
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

void CoutStatementNode::Code(InstructionsClass &machineCode) {
    mExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopAndWrite();
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

void IfStatementNode::Code(InstructionsClass &machineCode)
{
	mExpressionNode->CodeEvaluate(machineCode);
	unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
	unsigned char * address1 = machineCode.GetAddress();
	mStatementNode->Code(machineCode);
	unsigned char * address2 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddress, (int)(address2-address1));
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

void WhileStatementNode::Code(InstructionsClass &machineCode) {
    unsigned char * address1 = machineCode.GetAddress();
    mExpressionNode->CodeEvaluate(machineCode);
    unsigned char * InsertAddressToSkip = machineCode.SkipIfZeroStack();
    unsigned char * address2 = machineCode.GetAddress();
    mStatementNode->Code(machineCode);
    unsigned char * InsertAddressToJump = machineCode.Jump();
    unsigned char * address3 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddressToSkip, (int)(address3 - address2));
    machineCode.SetOffset(InsertAddressToJump, (int)(address1 - address3));
}

DoWhileStatementNode::DoWhileStatementNode(ExpressionNode* epn, StatementNode* sn) 
: mExpressionNode(epn), mStatementNode(sn) {
    MSG("Constructing Do While Statement Node");
}

DoWhileStatementNode::~DoWhileStatementNode() {
    MSG("Desctructing Do While Statement Node");
    delete mExpressionNode;
    delete mStatementNode;
}

void DoWhileStatementNode::Interpret() {
    do {
        mStatementNode->Interpret();
    } while (mExpressionNode->Evaluate() != 0);
}

void DoWhileStatementNode::Code(InstructionsClass &machineCode) {
    unsigned char * address1 = machineCode.GetAddress();
    mStatementNode->Code(machineCode);
    mExpressionNode->CodeEvaluate(machineCode);
    unsigned char * InsertAddressToSkip = machineCode.SkipIfZeroStack();
    unsigned char * address2 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddressToSkip, (int)(address1 - address2));
}


RepeatStatementNode::RepeatStatementNode(ExpressionNode* epn, StatementNode* sn)
: mExpressionNode(epn), mStatementNode(sn) {
    MSG("Constructing REPEAT Statement Node");
}

RepeatStatementNode::~RepeatStatementNode() {
    MSG("Desctructing REPEAT Statement Node");
    delete mExpressionNode;
    delete mStatementNode;
}

void RepeatStatementNode::Interpret() {
    int range = mExpressionNode->Evaluate();
    for (int i = 0; i < range; i++) {
        mStatementNode->Interpret();
    }
}

void RepeatStatementNode::Code(InstructionsClass &machineCode) {
    (void)machineCode;
    return;
    // mExpressionNode->CodeEvaluate(machineCode);
    // unsigned char * startAddress = machineCode.GetAddress();
    // unsigned char * skipToCondition = machineCode.Jump();
    // unsigned char * loopBodyStart = machineCode.GetAddress();
    // mStatementNode->Code(machineCode);
    // machineCode.DecrementStack();
    // unsigned char * conditionCheck = machineCode.GetAddress();
    // machineCode.CopyToStack();  // Ensure the loop counter remains for the next iteration
    // machineCode.SkipIfZeroStack();
    // unsigned char * endAddress = machineCode.GetAddress();
    // machineCode.SetOffset(conditionCheck, (int)(loopBodyStart - endAddress));
    // machineCode.SetOffset(skipToCondition, (int)(conditionCheck - loopBodyStart));
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

void IntegerNode::CodeEvaluate(InstructionsClass &machineCode) {
    machineCode.PushValue(mInteger);
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

void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode) {
    machineCode.PushVariable(this->GetIndex());
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

void PlusNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}


MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Minus Node");
}

int MinusNode::Evaluate() const {
    MSG("Evaluating Minus Node");
    return mLeftExpressionNode->Evaluate() - mRightExpressionNode->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Times Node");
}

int TimesNode::Evaluate() const {
    MSG("Evaluating Times Node");
    return mLeftExpressionNode->Evaluate() * mRightExpressionNode->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Divide Node");
}

int DivideNode::Evaluate() const {
    MSG("Evaluating Divide Node");
    return mLeftExpressionNode->Evaluate() / mRightExpressionNode->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
}

ModNode::ModNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Mod Node");
}

int ModNode::Evaluate() const {
    MSG("Evaluating Mod Node");
    return mLeftExpressionNode->Evaluate() % mRightExpressionNode->Evaluate();
}

void ModNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopModPush();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right) 
: BinaryOperatorNode(left, right) {
    MSG("Constructing OR Node");
}

int OrNode::Evaluate() const {
    MSG("Evaluating Or Node");
    return mLeftExpressionNode->Evaluate() || mRightExpressionNode->Evaluate() ? 1 : 0;
}

void OrNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopOrPush();
}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right) 
: BinaryOperatorNode(left, right) {
    MSG("Constructing AND Node");
}

int AndNode::Evaluate() const {
    MSG("Evaluating AND Node");
    return mLeftExpressionNode->Evaluate() && mRightExpressionNode->Evaluate() ? 1 : 0;
}

void AndNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopAndPush();
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Less Node");
}

int LessNode::Evaluate() const {
    MSG("Evaluating Less Node");
    return mLeftExpressionNode->Evaluate() < mRightExpressionNode->Evaluate() ? 1 : 0;
}

void LessNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Less Equal Node");
}

int LessEqualNode::Evaluate() const {
    MSG("Evaluating Less Equal Node");
    return mLeftExpressionNode->Evaluate() <= mRightExpressionNode->Evaluate() ? 1 : 0;
}

void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Greater Node");
}

int GreaterNode::Evaluate() const {
    MSG("Evaluating Greater Node");
    return mLeftExpressionNode->Evaluate() > mRightExpressionNode->Evaluate() ? 1 : 0;
}

void GreaterNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Greater Equal Node");
}

int GreaterEqualNode::Evaluate() const {
    MSG("Evaluating Greater Equal Node");
    return mLeftExpressionNode->Evaluate() >= mRightExpressionNode->Evaluate() ? 1 : 0;
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Equal Node");
}

int EqualNode::Evaluate() const {
    MSG("Evaluating Equal Node");
    return mLeftExpressionNode->Evaluate() == mRightExpressionNode->Evaluate() ? 1 : 0;
}

void EqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
: BinaryOperatorNode(left, right) {
    MSG("Constructing Not Equal Node");
}

int NotEqualNode::Evaluate() const {
    MSG("Evaluating Not Equal Node");
    return mLeftExpressionNode->Evaluate() != mRightExpressionNode->Evaluate() ? 1 : 0;
}

void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	mLeftExpressionNode->CodeEvaluate(machineCode);
	mRightExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopNotEqualPush();
}
