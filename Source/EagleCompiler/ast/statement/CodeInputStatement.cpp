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
	
	ret += "push dword terminalinput\n";
	ret += "call printf\n";
	ret += "add esp,4\n";
	

	if(v1->getType() == CodeType::INT32) {
		
		ret += "mov ecx,ebp\n";
		ret += "add ecx, byte " + to_string(v1->getVariable()->getStackPos()) + "\n";
		ret += "push ecx\n";
		ret += "push dword int32scan\n";
	} else if(v1->getType() == CodeType::STRING) {
		ret += v1->code();
		ret += "push eax\n";
		ret += "push dword stringscan\n";
	} else {
		throw std::exception();
	}
	ret += "call scanf\n";
	ret += "add esp,8\n";
	
	return ret;
}

