//
//  CodeExpressionFactorLiteral.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionFactorLiteral.h"

using namespace std;

string AST::CodeExpressionFactorLiteral::code() {
	return _value + ":" + _type->code();
}

