//
//  CodeIfStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeIfStatement.h"

using namespace std;

string AST::CodeIfStatement::code() {
	string ret;
	string ifStatementBlock;
	string elseStatementBlock;
	for(auto s : _ifStatements) {
		ifStatementBlock += s->code();
	}
	for(auto s : _elseStatements) {
		elseStatementBlock += s->code();
	}
	string ifLabel = "_"+to_string((long)this) + "_if";
	ret += _condition->code();
	ret += ifLabel + ":\n";//create a unique label for this statement
	ret += "cmp eax,0\n";
	ret += "je .else\n";
	ret += ifStatementBlock;
	ret += "jmp " + ifLabel + ".end\n";
	ret += ifLabel + ".else:\n";
	ret += elseStatementBlock;
	ret += ifLabel + ".end:\n";
	
	return ret;
}

