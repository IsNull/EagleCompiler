//
//  CodeExpressionUnaryExpression.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeExpressionUnaryExpression.h"

using namespace std;

namespace AST {
	map<UNARYOPERATOR, string> UnaryOperatorString = { 
		{ UNARYOPERATOR::NOT, "!" },  
		{ UNARYOPERATOR::NEGATIVE, "-" }, 
	};
}


string AST::CodeExpressionUnaryExpression::code() {
	string ret;
	
	ret += _expression->code();
	
	if(_unaryOperator == UNARYOPERATOR::NOT) {
		ret += "not eax\n";
	} else if(_unaryOperator == UNARYOPERATOR::NEGATIVE) {
		ret += "neg eax\n";
	}
	
	return ret;
}

