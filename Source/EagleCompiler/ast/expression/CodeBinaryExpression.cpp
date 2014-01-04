//
//  CodeBinaryExpression.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeBinaryExpression.h"

using namespace std;

namespace AST {
	map<BINARYOPERATOR, string> BinaryOperatorString = { 
		{ BINARYOPERATOR::TIMES, "*" },
		{ BINARYOPERATOR::DIV, "/" },
		{ BINARYOPERATOR::MOD, "%" },
		{ BINARYOPERATOR::PLUS, "+" },
		{ BINARYOPERATOR::MINUS, "-" },
		{ BINARYOPERATOR::LESS, "<" },
		{ BINARYOPERATOR::GREATER_EQ, ">=" },
		{ BINARYOPERATOR::EQUAL, "==" },
		{ BINARYOPERATOR::NOT_EQ, "!=" },
		{ BINARYOPERATOR::GREATER, ">" },
		{ BINARYOPERATOR::LESS_EQ, "<=" },
		{ BINARYOPERATOR::COND_AND, "&?" },
		{ BINARYOPERATOR::COND_OR, "|?" },
		{ BINARYOPERATOR::STR_CONCAT, "&" },
	};
}


string AST::CodeBinaryExpression::code() {
	return _left->code() + BinaryOperatorString[_binaryOperator] + _right->code();
}
