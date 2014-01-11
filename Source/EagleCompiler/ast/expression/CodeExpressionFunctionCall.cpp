//
//  CodeExpressionFunctionCall.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionFunctionCall.h"

using namespace std;

string AST::CodeExpressionFunctionCall::code() {
	string ret;
	for(auto e : _parameters) {
		string expr = e->code();
		expr += "push eax\n";
		ret = expr + ret;
	}
	
	ret += "call " + _function->code() + "\n";
	for(int i=0; i<_parameters.size(); i++) {
		ret += "pop ebx\n";
	}	
	return ret;
}

