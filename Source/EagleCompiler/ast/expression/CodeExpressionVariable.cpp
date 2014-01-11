//
//  CodeExpressionVariable.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionVariable.h"
#include "../identifier/CodeVariable.h"


using namespace std;

string AST::CodeExpressionVariable::code() {
	string ret;

	ret += "mov eax," + _variable->code() + "\n";
	
	return ret;
}

