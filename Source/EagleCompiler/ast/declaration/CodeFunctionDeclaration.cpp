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
	string params;
	string globalImports;
	string stoDecl;
	string code;
	for(auto e : _params) {
		params += e->code() + ",";
	}
	for(auto e : _globalImps) {
		globalImports += e->code() + ",";
	}
	for(auto e : _localStoDecls) {
		stoDecl += e->code() + ",";
	}
	for(auto e : _statements) {
		code += "  " + e->code() + "\n";
	}
	if(_params.size() > 0)_params.pop_back();
	if(_globalImps.size() > 0)_globalImps.pop_back();
	if(_localStoDecls.size() > 0)_localStoDecls.pop_back();
	
	return _function->code() + "(" + params + "):" + returnValue->code() + " " + globalImports + " " + stoDecl + "{\n" + code + "}";
}

