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
	
	
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string(_localStoDecls.size()) + "\n";
	
	ret += "leave\n";
	ret += "ret\n";
	

	string params;
	string globalImports;
	string stoDecl;
	string code;

	for(auto e : _globalImps) {
		globalImports += e->code() + ",";
	}
	for(auto e : _localStoDecls) {
		stoDecl += e->code() + ",";
	}
	for(auto e : _statements) {
		code += "  " + e->code() + "\n";
	}
	
	return ret;
}

