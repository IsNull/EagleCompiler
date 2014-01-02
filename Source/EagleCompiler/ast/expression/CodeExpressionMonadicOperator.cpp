//
//  CodeExpressionMonadicOperator.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeExpressionMonadicOperator.h"

using namespace std;

namespace AST {
	map<MONADICOPERATOR, string> MonadicOperatorString = { 
		{ MONADICOPERATOR::NOT, "!" },  
		{ MONADICOPERATOR::NEGATIVE, "-" }, 
	};
}


string AST::CodeExpressionMonadicOperator::code() {
	return MonadicOperatorString[_monadicOperator] + _factor->code();
}

