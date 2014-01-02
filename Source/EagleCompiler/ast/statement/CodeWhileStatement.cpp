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
	string statementBlock;
	for(auto s : _loopStatements) {
		statementBlock += "  " + s->code() + "\n";
	}
	return "while (" + _condition->code() + ") {\n" + statementBlock + "}";
}

