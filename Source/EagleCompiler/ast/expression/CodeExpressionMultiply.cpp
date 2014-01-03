//
//  CodeExpressionMultiply.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeExpressionMultiply.h"
#include "CodeExpressionFactor.h"

using namespace std;

namespace AST {
	map<MULTIPLYOPERATOR, string> MultiplyOperatorString = { 
		{ MULTIPLYOPERATOR::TIMES, "*" },  
		{ MULTIPLYOPERATOR::DIV, "-" }, 
		{ MULTIPLYOPERATOR::MOD, "%" }, 
	};
}

string AST::CodeExpressionMultiply::code() {
	string ret; 
	for(auto m : _factors) {
		ret += MultiplyOperatorString[m.first] + m.second->code();
	}
	return ret;
}

