//
//  CodeStorageDeclaration.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeStorageDeclaration.h"

#include "../type/CodeTypeString.h"

using namespace std;

string AST::CodeStorageDeclaration::code() {
	if(dynamic_cast<CodeTypeString*>(_variable->getType()) != nullptr) {
		return _variable->code() + ": times " + to_string(CodeTypeString::BUFFERLEN) + " " + _variable->getType()->code() + " 0\n";
	} else {
		return _variable->code() + ": " + _variable->getType()->code() + " 0\n";
	}
}

