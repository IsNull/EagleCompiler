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
	ret += "push dword eax\n";
	ret += "push int32print\n";
	ret += "call printf\n";
	ret += "add esp,8\n";
	return ret;
}

