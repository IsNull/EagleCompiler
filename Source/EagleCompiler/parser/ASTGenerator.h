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
#include "Parser.h"
#include "AST.h"

// TODO

using namespace std;
using namespace AST;

class ASTGenerator
{
private:
    vector<CodeParameter*> genCodeParameter(SyntaxTree* node);
    vector<CodeStatement*> genCodeStatements(SyntaxTree* node);
    vector<CodeDeclaration*> genCodeDeclarations(SyntaxTree* node);
    
    CodeProcedureDeclaration* genProcedureDecl(SyntaxTree* procDeclNode);
    
    SyntaxTree* findChildNonTerminal(SyntaxTree* parent, const string& name);
    SyntaxTree* findChildTerminal(SyntaxTree* parent, const TokenType token);
    
    SyntaxTree* findRecursiveNonTerminal(SyntaxTree* parent, const string& name, int maxDeepth=10);
    
    
public:
    CodeProgram* generate(SyntaxTree* syntaxParseTree);
};

#endif /* defined(__EagleCompiler__ASTGenerator__) */
