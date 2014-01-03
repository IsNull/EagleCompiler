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
    
public:
    CodeProgram* generate(SyntaxTree* syntaxParseTree);
};

#endif /* defined(__EagleCompiler__ASTGenerator__) */
