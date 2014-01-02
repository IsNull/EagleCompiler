//
//  CodeExpressionFactorFunctionCall.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeExpressionFactorFunctionCall.h"

using namespace std;

string AST::CodeExpressionFactorFunctionCall::code() {
	string params;
	for(auto e : _parameters) {
		params += e->code() + ",";
	}
	
	//remove last character
	if(_parameters.size() > 0) _parameters.pop_back();
	return _function->code() + "(" + params + ")";
}

