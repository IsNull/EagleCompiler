//
//  CodeWhileStatement.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeWhileStatement.h"

using namespace std;

string AST::CodeWhileStatement::code() {
	string ret;
	string statementBlock;
	string conditionBlock;
	string whileLable = "_"+to_string((long)this) + "_while";//create a unique label for this statement
	
	for(auto s : _loopStatements) {
		statementBlock += s->code();
	}
	
	conditionBlock = _condition->code();
	
	ret += whileLable + ":\n";
	ret += conditionBlock;
	ret += "cmp eax,0\n";
	ret += "je .end\n";
	ret += statementBlock;
	ret += "jmp " + whileLable + "\n";
	ret += ".end:\n";
	
	return ret;
}

