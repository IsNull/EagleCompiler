//
//  CodeExpressionStringConcatenation.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionStringConcatenation.h"
#include "CodeExpressionBoolean.h"

using namespace std;

string AST::CodeExpressionStringConcatenation::code() {
	string ret; 
	for(auto m : _booleanTerms) {
		ret += "&" + m->code();
	}
	return ret;
}

