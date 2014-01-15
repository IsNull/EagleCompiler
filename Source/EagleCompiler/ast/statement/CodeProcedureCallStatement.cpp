//
//  CodeProcedureCallStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProcedureCallStatement.h"
#include "../declaration/CodeProcedureDeclaration.h"
#include "../expression/CodeExpressionVariable.h"
#include "../CodeProgram.h"

using namespace std;

string AST::CodeProcedureCallStatement::code() {
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

	ret += "call " + _procedure->code() + "\n";

	
	for(int i=0; i<_procedure->getDeclaration()->getParameters().size(); i++){
		auto e = _procedure->getDeclaration()->getParameters()[i];
		if( e->getFlowMode() == FLOWMODE::OUT || e->getFlowMode() == FLOWMODE::INOUT) {
			if(e->getVariable()->getType() == CodeType::INT32 || e->getVariable()->getType() == CodeType::BOOL)  {
				CodeExpressionVariable *v = dynamic_cast<CodeExpressionVariable *>(_parameters[i]);
				if(v != nullptr) {
					ret += "pop dword " + v->getVariable()->code() + "\n";
				} else {
					throw runtime_error("OUT or INOUT parameters must be a variable");
				}
			} else if(e->getVariable()->getType() == CodeType::STRING) {
				CodeExpressionVariable *v = dynamic_cast<CodeExpressionVariable *>(_parameters[i]);
				if(v != nullptr) {					
					ret += "push dword " + to_string(STRING::BUFFER_LEN-1) + "\n";
					ret += "push " + e->getVariable()->label() + "\n";
					ret += _parameters[i]->code();
					ret += "push eax\n";
					ret += "call " + CodeProgram::STRNCPY + "\n";
					ret += "add esp,12\n";
					
				} else {
					throw runtime_error("OUT or INOUT parameters must be a variable");
				}
			}
		} else {
			ret += "pop edx\n";
		}
	}

	ret += "add esp," + to_string(usedParameters*4) + "\n";

	return ret;
}

