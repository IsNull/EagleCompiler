//
//  CodeProcedureDeclaration.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProcedureDeclaration.h"

using namespace std;

string AST::CodeProcedureDeclaration::code() {
	string ret;
	
	for(int i=0; i<_params.size(); i++) {
		_params[i]->getVariable()->setStackPos(8 + (4*i));
	}
	
	for(int i=0; i<_localStoDecls.size(); i++) {
		_localStoDecls[i]->getVariable()->setStackPos(-4-(4*i));
	}
	
	ret += getIdentifier()->code() + ":\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string((_localStoDecls.size())*4) + "\n";
	
	for(auto s : _statements) {
		ret += s->code();
	}

	ret += "mov esp,ebp\n";
	ret += "pop ebp\n";
	ret += "ret\n";
	
	return ret;
}

