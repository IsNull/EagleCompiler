//
//  CodeProcedureDeclaration.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProcedureDeclaration.h"
#include "../CodeProgram.h"

using namespace std;

string AST::CodeProcedureDeclaration::code() {
	string ret;
	string stringParameterCopies;
	
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
	
	for(auto e : _globalImps) {
		cout << "##################Global import:" << e->getVariable()->getName() << ": " << e->getVariable()->code() << endl;
	}
	
	for(int i=0; i<_localStoDecls.size(); i++) {
		_localStoDecls[i]->getVariable()->setStackPos(-4-(4*i));
	}
	
	ret += getIdentifier()->code() + ":\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string((_localStoDecls.size())*4) + "\n";
	ret += stringParameterCopies;
	
	for(auto s : _statements) {
		ret += s->code();
	}

	ret += "mov esp,ebp\n";
	ret += "pop ebp\n";
	ret += "ret\n";
	
	return ret;
}

