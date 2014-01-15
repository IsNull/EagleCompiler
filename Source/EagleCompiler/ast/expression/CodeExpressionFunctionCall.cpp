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
	
	int usedParameters=0;

	for(auto e : _parameters) {
		if(e != nullptr) {
			string expr = e->code();
			expr += "push eax\n";
			ret = expr + ret;
			usedParameters++;
		}
	}

	
	ret += "call " + _function->code() + "\n";
	ret += "add esp," + to_string(usedParameters*4) + "\n";
	
	return ret;
}

