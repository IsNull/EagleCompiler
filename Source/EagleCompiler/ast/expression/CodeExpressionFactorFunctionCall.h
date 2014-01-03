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

#include "CodeExpressionFactor.h"
#include "CodeExpression.h"
#include "../identifier/CodeFunction.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorFunctionCall : public CodeExpressionFactor {
	private:
		CodeFunction *_function;
		vector<CodeExpression*> _parameters;
	public:
		CodeExpressionFactorFunctionCall(CodeFunction *function) : _function(function) { };
		
		void addParameter(CodeExpression *expression) 
			{ _parameters.push_back(expression); }
		
		CodeFunction *getFunction()
			{ return _function; };
		
		auto getParameters() -> decltype(_parameters)
			{ return _parameters; };
		
		string code();
	};
}

#endif

