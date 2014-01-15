//
//  CodeFunctionDeclaration.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeFunctionDeclaration.h"
#include "../CodeProgram.h"

using namespace std;

string AST::CodeFunctionDeclaration::code() {
	string ret,stringParameterCopies;
	
	for(int i=0; i<_params.size(); i++) {
		_params[i]->getVariable()->setStackPos(8 + (4*i));
		if(_params[i]->getVariable()->getType() == CodeType::STRING) {
			stringParameterCopies += "push dword " + to_string(STRING::BUFFER_LEN-1) + "\n";
			stringParameterCopies += "push dword " + _params[i]->getVariable()->code() + "\n";
			stringParameterCopies += "push dword " + _params[i]->getVariable()->label() + "\n";
			stringParameterCopies += "call " + CodeProgram::STRNCPY + "\n";
			stringParameterCopies += "add esp,12\n";
		}
	}
	_returnValue->getVariable()->setStackPos(-4);
	for(int i=0; i<_localStoDecls.size(); i++) {
		_localStoDecls[i]->getVariable()->setStackPos(-8-(4*i));
	}
	
	ret += getIdentifier()->code() + ":\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string((_localStoDecls.size()+1)*4) + "\n";
	
	ret += stringParameterCopies;
	
	for(auto s : _statements) {
		ret += s->code();
	}
	if(_returnValue->getVariable()->getType() == CodeType::STRING) {
		ret += "mov eax," + _returnValue->getVariable()->label() + "\n";
	} else if (_returnValue->getVariable()->getType() == CodeType::INT32 || _returnValue->getVariable()->getType() == CodeType::BOOL) {
		ret += "mov eax," + _returnValue->getVariable()->code() + "\n";
	} else {
		throw std::runtime_error("not valid return type");
	}
	ret += "mov esp,ebp\n";
	ret += "pop ebp\n";
	ret += "ret\n";
	
	return ret;
}

