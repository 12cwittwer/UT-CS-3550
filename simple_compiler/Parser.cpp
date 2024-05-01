#include "Parser.h"

ProgramNode * ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode *bn = Block();
    ProgramNode *pn = new ProgramNode(bn);
    return pn;
}

BlockNode * ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroupNode *sg = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode *bn = new BlockNode(sg);
    return bn;
}

StatementGroupNode * ParserClass::StatementGroup() { //Need to write case for when StatementGroup is empty
    StatementGroupNode *sg = new StatementGroupNode();
    StatementNode *sn = Statement();
    while (sn) {
        sg->AddStatement(sn);
        sn = Statement();
    }
    return sg;
    // StatementGroupNode *sg = new StatementGroupNode();
    // StatementNode *sn = Statement();
    // if(sn) {
    //     sg->AddStatement(sn);
    //     StatementGroup();
    //     return sg;
    // } else {
    //     return sg;
    // }
}

StatementNode * ParserClass::Statement() { // Add if and while statements here
    TokenClass nextTokenClass = mScannerClass->PeekNextToken();
    TokenType nextToken = nextTokenClass.GetTokenType();
    StatementNode *sn = NULL;
    if (nextToken == INT_TOKEN) {
        sn = DeclarationStatement();
        return sn;
    } else if (nextToken == IDENTIFIER_TOKEN) {
        sn = AssignmentStatement();
        return sn;
    } else if (nextToken == COUT_TOKEN) {
        sn = CoutStatement();
        return sn;
    } else if (nextToken == LCURLY_TOKEN) {
        sn = Block();
        return sn;
    } else if (nextToken == IF_TOKEN) {
        sn = IfStatement();
        return sn;
    } else if (nextToken == WHILE_TOKEN) {
        sn = WhileStatement();
        return sn;
    } else if (nextToken == REPEAT_TOKEN) {
        sn = RepeatStatement();
        return sn;
    } else if (nextToken == DO_TOKEN) {
        sn = DoWhileStatement();
        return sn;
    } else {
        return NULL;
    }
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    IdentifierNode *id = Identifier();
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode *ds = new DeclarationStatementNode(id);
    return ds;
}

StatementNode * ParserClass::AssignmentStatement() { // Branch for the three different scenarios
    IdentifierNode *id = Identifier();
    TokenClass nextTokenClass = mScannerClass->PeekNextToken();
    TokenType nextToken = nextTokenClass.GetTokenType();
    StatementNode *as = NULL;
    if (nextToken == ASSIGNMENT_TOKEN) {
        Match(nextToken);
        ExpressionNode *ex = Expression();
        Match(SEMICOLON_TOKEN);
        as = new AssignmentStatementNode(id, ex);
        return as;
    } else if (nextToken == PLUSEQUAL_TOKEN) {
        Match(nextToken);
        ExpressionNode *ex = Expression();
        Match(SEMICOLON_TOKEN);
        as = new PlusEqualStatementNode(id, ex);
        return as;
    } else if (nextToken == MINUSEQUAL_TOKEN) {
        Match(nextToken);
        ExpressionNode *ex = Expression();
        Match(SEMICOLON_TOKEN);
        as = new MinusEqualStatementNode(id, ex);
        return as;
    } else {
        return NULL;
    }
}

CoutStatementNode * ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode *ex = Expression();
    Match(SEMICOLON_TOKEN);
    CoutStatementNode *cs = new CoutStatementNode(ex);
    return cs;
}

IfStatementNode * ParserClass::IfStatement() {
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *epn = Expression();
    Match(RPAREN_TOKEN);
    StatementNode *sn = Statement();
    IfStatementNode *ifn = new IfStatementNode(epn, sn);
    return ifn;
}

WhileStatementNode * ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *epn = Expression();
    Match(RPAREN_TOKEN);
    StatementNode *sn = Statement();
    WhileStatementNode *wsn = new WhileStatementNode(epn, sn);
    return wsn;
}

DoWhileStatementNode * ParserClass::DoWhileStatement() {
    Match(DO_TOKEN);
    StatementNode *sn = Statement();
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *epn = Expression();
    Match(RPAREN_TOKEN);
    Match(SEMICOLON_TOKEN);
    DoWhileStatementNode *dsn = new DoWhileStatementNode(epn, sn);
    return dsn;
}

RepeatStatementNode * ParserClass::RepeatStatement() {
    Match(REPEAT_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *epn = Expression();
    Match(RPAREN_TOKEN);
    StatementNode *sn = Statement();
    RepeatStatementNode *rsn = new RepeatStatementNode(epn, sn);
    return rsn;
}


IdentifierNode * ParserClass::Identifier() {
    std::string label = Match(IDENTIFIER_TOKEN).GetLexeme();
    IdentifierNode *in = new IdentifierNode(label, mSymbolTableClass);
    return in;
}

ExpressionNode * ParserClass::Expression() {
    return Or();
}

ExpressionNode * ParserClass::Or() {
	ExpressionNode * current = And();
	while(true)
	{
		TokenType tt = mScannerClass->PeekNextToken().GetTokenType();
		if(tt == OR_TOKEN)
		{
			Match(tt);
            current = new OrNode(current, And());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode * ParserClass::And() {
    ExpressionNode * current = Relational();
	while(true)
	{
		TokenType tt = mScannerClass->PeekNextToken().GetTokenType();
		if(tt == AND_TOKEN)
		{
			Match(tt);
            current = new AndNode(current, Relational());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode * ParserClass::Relational()
{
    ExpressionNode *current = PlusMinus();

	// Handle the optional tail:
	TokenType tt = mScannerClass->PeekNextToken().GetTokenType();
	if(tt == LESS_TOKEN)
	{
		Match(tt);
		current = new LessNode(current, PlusMinus());
	}
	else if(tt == LESSEQUAL_TOKEN)
	{
		Match(tt);
        current = new LessEqualNode(current, PlusMinus());
	}
	else if(tt == GREATER_TOKEN)
	{
		Match(tt);
        current = new GreaterNode(current, PlusMinus());
	}
	else if(tt == GREATEREQUAL_TOKEN)
	{
		Match(tt);
        current = new GreaterEqualNode(current, PlusMinus());
	}
	else if(tt == EQUAL_TOKEN)
	{
		Match(tt);
        current = new EqualNode(current, PlusMinus());
	}
	else if(tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
        current = new NotEqualNode(current, PlusMinus());
	}
	return current;
}


ExpressionNode * ParserClass::PlusMinus()
{
	ExpressionNode * current = TimesDivide();
	while(true)
	{
		TokenType tt = mScannerClass->PeekNextToken().GetTokenType();
		if(tt == PLUS_TOKEN)
		{
			Match(tt);
            current = new PlusNode(current, TimesDivide());
		}
		else if(tt == MINUS_TOKEN)
		{
			Match(tt);
            current = new MinusNode(current, TimesDivide());
		}
        else if (tt == MOD_TOKEN) {
            Match(tt);
            current = new ModNode(current, TimesDivide());
        }
		else
		{
			return current;
		}
	}
}


ExpressionNode * ParserClass::TimesDivide() {
    ExpressionNode * current = Factor();
    while(true) {
        TokenType tt = mScannerClass->PeekNextToken().GetTokenType();
        if (tt == TIMES_TOKEN) {
            Match(tt);
            current = new TimesNode(current, Factor());
        } else if (tt == DIVIDE_TOKEN) {
            Match(tt);
            current = new DivideNode(current, Factor());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::Factor() {
    ExpressionNode * current;
    TokenType next_token = mScannerClass->PeekNextToken().GetTokenType();
    if (next_token == IDENTIFIER_TOKEN) {
        current = Identifier();
    } else if (next_token == INTEGER_TOKEN) {
        current = Integer();
    } else if (next_token == LPAREN_TOKEN) {
        Match(LPAREN_TOKEN);
        current = Expression();
        Match(RPAREN_TOKEN);
    } else {
        std::cerr << "Error in ParserClass::Factor." << std::endl;
        std::cerr << "Expected Token Type Identifier, Integer, or LPAREN, but, got type " 
            << TokenClass::GetTokenTypeName(next_token) << std::endl;
        exit(1);
    }
    return current;
}

IntegerNode * ParserClass::Integer() {
    std::string lexeme = Match(INTEGER_TOKEN).GetLexeme();
    int num = std::atoi(lexeme.c_str());
    IntegerNode *in = new IntegerNode( num );
    return in;
}

ParserClass::ParserClass(ScannerClass* sc, SymbolTableClass* stc) 
:mScannerClass(sc), mSymbolTableClass(stc) {
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass currentToken = mScannerClass->GetNextToken();
    if(currentToken.GetTokenType() != expectedType) {
        std::cerr << "Error in ParserClass::Match. " << std::endl;
        std::cerr << "Expected token type " << 
            TokenClass:: GetTokenTypeName(expectedType) << 
        ", but got type " << currentToken.GetTokenTypeName() << std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " << 
    currentToken.GetTokenTypeName() << ". Lexeme: \"" << 
    currentToken.GetLexeme() << "\"");
    return currentToken; // the one we just processed
}

StartNode * ParserClass::Start() {
    ProgramNode * pn = Program();
    Match( ENDFILE_TOKEN );
    StartNode *sn = new StartNode(pn);
    return sn;
}