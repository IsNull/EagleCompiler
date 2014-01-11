//
//  CodeProcedureCallStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProcedureCallStatement.h"

using namespace std;

string AST::CodeProcedureCallStatement::code() {
	string params;
	for(auto e : _parameters) {
		string expr = e->toCode();
		expr += "push eax\n"
		params = expr + params;
	}
	
	//remove last character
	if(_parameters.size() > 0)_parameters.pop_back();
	return "call " + _procedure->code() + "(" + params + ")";
}

