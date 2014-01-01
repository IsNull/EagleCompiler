//
//  CodeExpressionFactorFunctionCall
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorFunctionCall__
#define __EagleCompiler__CodeExpressionFactorFunctionCall__

#include <string>

#include "CodeExpression.h"
#include "CodeExpressionFactor.h"
#include "../identifier/CodeFunction.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorFunctionCall : public CodeExpressionFactor {
	private:
		CodeFunction *_function;
		vector<CodeExpression> _parameters;
	public:
		CodeExpressionFactorFunctionCall(CodeFunction *function) : _function(function) { };
		
		CodeFunction *getFunction() { return _function; };
		vector<CodeExpression>& getParameters() { return _parameters; };
		
		string code();
	};
}

#endif

