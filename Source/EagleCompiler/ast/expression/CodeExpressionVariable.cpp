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

	if(_variable->getType() == CodeType::INT32 || _variable->getType() == CodeType::BOOL) {
		ret += "mov eax," + _variable->code() + "\n";
	} else if(_variable->getType() == CodeType::STRING) {
		ret += "mov eax," + _variable->label() + "\n";
	} else {
		throw std::exception();
	}
	
	return ret;
}

