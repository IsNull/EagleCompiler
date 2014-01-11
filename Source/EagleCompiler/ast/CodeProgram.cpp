//
//  CodeProgram.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProgram.h"

#include "declaration/CodeStorageDeclaration.h"

using namespace std;

string AST::CodeProgram::code() {
	
	//Prepare variables
	for (int i=0; i<_globalDecl.size(); i++) {
		CodeStorageDeclaration * decl = dynamic_cast<CodeStorageDeclaration*>(_globalDecl[i]);
		if(decl != nullptr) {
			decl->getVariable()->setStackPos(-i*4);
		}
	}
	string ret = "global main\n\n";
	ret += "extern  printf\n";
	
	ret += "\n";
	
	ret += "section .data\n";
	ret += "int32print: db \"%d\",10,0\n";
	ret += "stringprint: db \"%s\",10,0\n";
	ret += "\n";
	
	ret += "section .text\n";
	ret += "main:\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string(_globalDecl.size()) + "\n";

	for (auto p : _progStatements) {
		ret += p->code();
	}
	ret += "leave\n";
	ret += "ret\n";
	
	return ret;
}

