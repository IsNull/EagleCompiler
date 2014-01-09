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
	
}


string AST::CodeBinaryExpression::code() {
	return _left->code() + AST::BinaryOperatorString.find(_binaryOperator)->second + _right->code();
}
