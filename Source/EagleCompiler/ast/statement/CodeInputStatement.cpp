//
//  CodeInputStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeInputStatement.h"

#include "../expression/CodeExpressionVariable.h"

using namespace std;

string AST::CodeInputStatement::code() {
	string ret;
	
	CodeExpressionVariable *v1 = dynamic_cast<CodeExpressionVariable*>(_expression);
	if(v1 == nullptr) {
		throw std::exception();
	}
	
	ret += _expression->code();
	ret += "push dword " + v1->code() + "\n";
	ret += "push int32print\n";
	ret += "call scanf\n";
	ret += "pop eax\n";
	ret += "pop eax\n";
	return ret;
	
	return ret;
}

