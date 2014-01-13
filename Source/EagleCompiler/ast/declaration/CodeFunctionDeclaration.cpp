//
//  CodeFunctionDeclaration.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeFunctionDeclaration.h"

using namespace std;

string AST::CodeFunctionDeclaration::code() {
	string ret;
	
	for(int i=0; i<_params.size(); i++) {
		_params[i]->getVariable()->setStackPos(8 + (4*i));
	}
	
	
	
	ret += getIdentifier()->getName() + ":\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string((_localStoDecls.size()+1)*4) + "\n";
	_returnValue->getVariable()->setStackPos(0);
	
	for(auto s : _statements) {
		ret += s->code();
	}
	if(_returnValue->getVariable()->getType() == CodeType::STRING) {
		ret += "mov eax" + _returnValue->getVariable()->label() + "\n";
	} else {
		ret += "mov eax" + _returnValue->getVariable()->code() + "\n";
	}
	ret += "leave\n";
	ret += "ret\n";
	
	return ret;
}

