//
//  CodeStorageDeclaration.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeStorageDeclaration.h"

using namespace std;

string AST::CodeStorageDeclaration::code() {
	if(_variable->getType() == CodeType::STRING) {
		return _variable->code() + ": times " + to_string(STRING::BUFFER_LEN) + " db 0\n";
	} else {
		return _variable->code() + ": dd 0\n";
	}
}

