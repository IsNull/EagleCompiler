//
//  ASTGenerator.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 14.12.13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__ASTGenerator__
#define __EagleCompiler__ASTGenerator__

#include <iostream>
#include <string>
#include <set>
#include "Parser.h"
#include "../ast/AST.h"

// TODO

using namespace std;
using namespace AST;



const map<TokenType, BINARYOPERATOR> BINARYOPERATOR_MAP = {
    {Operator_Plus, BINARYOPERATOR::PLUS},
    {Operator_Minus, BINARYOPERATOR::MINUS},
    {Operator_Div, BINARYOPERATOR::DIV},
    {Operator_Multiply, BINARYOPERATOR::TIMES},
    {Operator_Modulo, BINARYOPERATOR::MOD},
    {Operator_Equals,BINARYOPERATOR::EQUAL},
    {Operator_GreaterThan, BINARYOPERATOR::GREATER},
    {Operator_SmallerThan, BINARYOPERATOR::LESS},
    {Operator_GreaterThanOrEqual, BINARYOPERATOR::GREATER_EQ},
    {Operator_SmallerThanOrEqual, BINARYOPERATOR::LESS_EQ},
    {Operator_StringConcat, BINARYOPERATOR::STR_CONCAT},
    {Operator_BOOL_AND, BINARYOPERATOR::COND_AND},
    {Operator_BOOL_OR, BINARYOPERATOR::COND_OR},
    //{Operator_BOOL_CAND,},
    //{Operator_BOOL_COR}
};

class ASTGenerator
{
private:
    CodeProgram* _program;
    SyntaxTree* _rootNode;
    
    CodeVariable* findGlobalVariable(const string& name);
    CodeFunction* findGlobalFunction(const string& name);
    CodeProcedure* findGlobalProcedure(const string& name);
    
    CodeStatement* genCodeStatement(SyntaxTree* node);
    CodeType genCodeType(SyntaxTree* atomTypeNode);
    CodeParameter* genCodeParameter(SyntaxTree* node);
    CodeExpression* genExpression(SyntaxTree* exprNode);
    CodeExpression* genOperatorExpression(SyntaxTree* exprNode);
    CodeBinaryExpression* genBinaryExpression(CodeExpression* leftSide, SyntaxTree* operatorTerminalNode, CodeExpression* rightSide);
    CodeBinaryExpression* genBinaryExpression(CodeExpression* leftSideExpr, SyntaxTree* repNode);

    vector<SyntaxTree*> findCommandNodes(SyntaxTree* cmdNode);
    
    vector<CodeExpression*> genCodeExpressionList(SyntaxTree* node);
    vector<CodeParameter*> genCodeParameters(SyntaxTree* node);
    vector<CodeStatement*> genCodeStatements(SyntaxTree* node);
    vector<CodeDeclaration*> genCodeDeclarations(SyntaxTree* node);
    
    CodeInvokableDeclaration* genInvokableDecl(SyntaxTree* procDeclNode, bool isfunction);
    
    /**
     * Searches the next Terminal starting at parent (recursive)
     */
    SyntaxTree* findNextTerminalRec(SyntaxTree* parent, TokenType ignoreToken);
    SyntaxTree* findChildNonTerminal(SyntaxTree* parent, const string& name);
    SyntaxTree* findChildTerminal(SyntaxTree* parent, const TokenType token);
    SyntaxTree* findChildTerminal(SyntaxTree* parent, const string terminalName);
    
    SyntaxTree* findRecursiveNonTerminal(SyntaxTree* parent, const string& name, int maxDeepth=10);
    
    vector<SyntaxTree*> findAllNonTerminals(SyntaxTree* parent, const string& name);
    vector<SyntaxTree*> findAllNonTerminalRec(SyntaxTree* parent, const string& name, bool searchNested = false);
    vector<SyntaxTree*> findAllNonTerminalRecExcluding(SyntaxTree* parent, const string& name, set<string> excludeSet);
	
	map<string, CodeVariable*> _variables;
	string _context;
    
public:
    /**
     * Create an AST Generator for the given SyntaxTree
     */
    ASTGenerator(SyntaxTree* syntaxTree)
        : _rootNode(syntaxTree) { }
    
    CodeProgram* generate();
};

#endif /* defined(__EagleCompiler__ASTGenerator__) */
