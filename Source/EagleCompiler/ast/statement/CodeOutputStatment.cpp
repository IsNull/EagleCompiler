//
//  CodeOutputStatment.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeOutputStatment.h"

using namespace std;

string AST::CodeOutputStatment::code() {
	string ret;
	
	ret += _expression->code();
	if(_expression->getType() == CodeType::INT32 ) {
		ret += "push eax\n";
		ret += "push dword int32print\n";
	} else if(_expression->getType() == CodeType::BOOL) {
		ret += to_string((long)this) + "_booltostring: ";
		ret += "cmp eax,0\n";
		ret += "mov eax,booltostringfalse\n";
		ret += "je .booljmp\n";
		ret += "mov eax,booltostringtrue\n";
		ret += "push eax\n";
		ret += ".booljmp: push stringprint\n";
	} else if(_expression->getType() == CodeType::STRING) {
		ret += "push eax\n";
		ret += "push dword stringprint\n";
	} else {
		throw std::exception();
	}
	ret += "call printf\n";
	ret += "add esp,8\n";
	return ret;
}

