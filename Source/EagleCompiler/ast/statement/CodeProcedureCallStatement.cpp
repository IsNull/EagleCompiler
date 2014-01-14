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
	string ret;
	
	for(auto e : _parameters) {
		string expr = e->code();
		expr += "push eax\n";
		ret = expr + ret;
	}
	
	ret += "call " + _procedure->code() + "\n";
	ret += "add esp," + to_string(_parameters.size()*4) + "\n";

	return ret;
}

