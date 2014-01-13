//
//  CodeExpressionLiteral.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionLiteral.h"

using namespace std;

vector<AST::CodeExpressionLiteral*> AST::CodeExpressionLiteral::literals;

string AST::CodeExpressionLiteral::code() {
	string ret;
	
	if(_variable->getType() == CodeType::INT32) {
		ret += "mov eax," + _value + "\n";
	} else if (_variable->getType() == CodeType::BOOL) {
		if(_value[0] == 't' || _value[0] == 'T') {
			ret += "mov eax,1\n";
		}else if(_value[0] == 'f' || _value[0] == 'F') {
			ret += "mov eax,0\n";
		}
	}else if(_variable->getType() == CodeType::STRING) {
		ret += "mov eax," + _variable->label() + "\n";
	}
	
	return ret;
}

