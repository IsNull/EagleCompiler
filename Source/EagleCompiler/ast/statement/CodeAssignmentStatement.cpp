//
//  CodeAssignmentStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <exception>

#include "../CodeProgram.h"
#include "CodeAssignmentStatement.h"
#include "../expression/CodeExpressionVariable.h"
#include "../type/CodeType.h"

using namespace std;

string AST::CodeAssignmentStatement::code() {
	string ret;
	
	CodeExpressionVariable *dest = dynamic_cast<CodeExpressionVariable*>(_lvalue);
	if(dest != nullptr) {
		if(dest->getVariable()->getType() == CodeType::INT32 || dest->getVariable()->getType() == CodeType::BOOL) {
			ret += _rvalue->code();
			ret += "mov " + dest->getVariable()->code() + ",eax\n";
		} else if (dest->getVariable()->getType() == CodeType::STRING) {
			ret += _rvalue->code();
			
			if(_rvalue->getType() == CodeType::INT32) {				
				ret += "push eax\n";
				ret += "push int32print\n";
				ret += "push " + to_string(STRING::BUFFER_LEN-1) + "\n";
				ret += "push "+ CodeProgram::tmp1->label() +"\n";
				ret += "call " + CodeProgram::SNPRINTF + "\n";
				ret += "mov eax," + CodeProgram::tmp1->label() + "\n";
			} else if(_rvalue->getType() == CodeType::BOOL) {
				ret += "cmp eax,0\n";
				ret += "mov eax,booltostringfalse\n";
				ret += "je .booljmp\n";
				ret += "mov eax,booltostringtrue\n";
				ret += ".booljmp:\n";
			}
			
			ret += "push " + to_string(STRING::BUFFER_LEN-1) + "\n";
			ret += "push eax\n";
			ret += dest->code();
			ret += "push eax\n";
			ret += "call " + CodeProgram::STRNCPY + "\n";
			ret += "add esp,12\n";
		}

	} else {
		throw std::exception();
	}
	
	return ret;
}

