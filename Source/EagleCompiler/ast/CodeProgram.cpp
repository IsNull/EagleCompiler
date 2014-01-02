//
//  CodeProgram.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProgram.h"

using namespace std;

string AST::CodeProgram::code() {
	string ret = "progParams:\n";
	
	for (auto p : _progParams) {
		ret += p->code() + "\n";
	}
	
	ret += "\nglobalDecl:\n";
	for (auto p : _globalDecl) {
		ret += p->code() + "\n";
	}
	
	ret += "\nprogStatements:\n";
	for (auto p : _progStatements) {
		ret += "  " + p->code() + "\n";
	}
	
	ret += "\n";
	return ret;
}

