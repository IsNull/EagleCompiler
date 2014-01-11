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
	
	string ret = "global main\n\n";
	ret += "extern  printf\n";
	
	ret += "\n";
	
	for (auto p : _progParams) {
		ret += p->code() + "\n";
	}
	
	ret += "section .data\n";
	ret += "int32print: db \"%d\",10,0\n";
	ret += "stringprint: db \"%s\",10,0\n";
	for (auto p : _globalDecl) {
		ret += p->code();
	}
	ret += "\n";
	
	ret += "section .text\n";
	ret += "main:\n";
	for (auto p : _progStatements) {
		ret += p->code();
	}
	
	return ret;
}

