//
//  CodeExpressionLiteral.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionLiteral.h"

using namespace std;

vector<AST::CodeExpressionLiteral*> AST::CodeExpressionLiteral::literals;

string AST::CodeExpressionLiteral::code() {
	string ret;
	ret += "mov eax," + _variable->label() + "\n";
	
	return ret;
}

