//
//  CodeExpressionFactorLiteral
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorLiteral__
#define __EagleCompiler__CodeExpressionFactorLiteral__

#include <string>

#include "CodeExpression.h"
#include "CodeExpressionFactor.h"
#include "../identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorLiteral : public CodeExpressionFactor {
	private:
		CodeVariable *_value;
	public:
		CodeExpressionFactorLiteral(CodeVariable *value) : _value(value) { };
		
		CodeVariable *getVariable() { return _value; };
		
		string code();
	};
}

#endif

