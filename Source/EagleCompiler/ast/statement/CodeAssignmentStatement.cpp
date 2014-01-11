//
//  CodeAssignmentStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <exception>

#include "CodeAssignmentStatement.h"
#include "../expression/CodeExpressionInitializeVariable.h"

using namespace std;

string AST::CodeAssignmentStatement::code() {
	string ret;
	
	CodeExpressionVariable *v1 = dynamic_cast<CodeExpressionVariable*>(_lvalue);
	if(v1 != nullptr) {
		ret += _rvalue->code();
		ret += "mov " + v1->getVariable()->code() + ",eax\n";
	} else {
		throw std::exception();
	}
	
	return ret;
}

