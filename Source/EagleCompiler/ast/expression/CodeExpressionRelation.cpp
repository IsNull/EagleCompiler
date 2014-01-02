//
//  CodeExpressionRelation.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeExpressionRelation.h"
#include "CodeExpressionAdd.h"

using namespace std;

namespace AST {
	map<RELATIONOPERATOR, string> RelationOperatorString = { 
		{ RELATIONOPERATOR::EQ, "==" }, 
		{ RELATIONOPERATOR::NE, "!=" },
		{ RELATIONOPERATOR::GE, ">=" }, 
		{ RELATIONOPERATOR::GT, ">" },
		{ RELATIONOPERATOR::LE, "<=" }, 
		{ RELATIONOPERATOR::LT, "<" },
	};
}

string AST::CodeExpressionRelation::code() {
	return _left->code() + RelationOperatorString[_op] + _right->code();
}

