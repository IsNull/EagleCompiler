//
//  CodeExpressionFactorInitialize
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorInitialize__
#define __EagleCompiler__CodeExpressionFactorInitialize__

#include <string>

#include "CodeExpressionFactor.h"
#include "../identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorInitialize : public CodeExpressionFactor {
	private:
		CodeVariable *_variable;
	public:
		CodeExpressionFactorInitialize(CodeVariable *variable) : _variable(variable) { };
		
		CodeVariable *getVariable() { return _variable; };
		
		string code();
	};
}

#endif

