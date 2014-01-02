//
//  CodeExpressionBoolean.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeExpressionBoolean.h"
#include "CodeExpressionRelation.h"

using namespace std;

namespace AST {
	map<BOOLEANOPERATOR, string> BooleanOperatorString = { 
		{ BOOLEANOPERATOR::AND, "&&" }, 
		{ BOOLEANOPERATOR::OR, "||" },
		{ BOOLEANOPERATOR::CAND, "&?" }, 
		{ BOOLEANOPERATOR::COR, "|?" },
	};
}

string AST::CodeExpressionBoolean::code() {
	string ret; 
	for(auto m : _relations) {
		ret += BooleanOperatorString[m.first] + m.second->code();
	}
	return ret;
}

