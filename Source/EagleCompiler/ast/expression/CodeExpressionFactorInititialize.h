//
//  CodeExpressionFactorInititialize
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorInititialize__
#define __EagleCompiler__CodeExpressionFactorInititialize__

#include <string>

#include "CodeExpression.h"
#include "CodeExpressionFactor.h"
#include "../identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorInititialize : public CodeExpressionFactor {
	private:
		CodeVariable *_variable;
	public:
		CodeExpressionFactorInititialize(CodeVariable *variable) : _variable(variable) { };
		
		CodeVariable *getVariable() { return _variable; };
		
		string code();
	};
}

#endif

