//
//  CodeExpressionAdd.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeExpressionAdd.h"
#include "CodeExpressionMultiply.h"

using namespace std;

namespace AST {
	map<ADDOPERATOR, string> AddOperatorString = { 
		{ ADDOPERATOR::PLUS, "+" },  
		{ ADDOPERATOR::MINUS, "-" }, 
	};
}

string AST::CodeExpressionAdd::code() {
	string ret; 
	for(auto m : _multiplys) {
		ret += AddOperatorString[m.first] + m.second->code();
	}
	return ret;
}

