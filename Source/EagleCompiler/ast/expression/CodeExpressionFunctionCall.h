//
//  CodeExpressionFunctionCall
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFunctionCall__
#define __EagleCompiler__CodeExpressionFunctionCall__

#include <string>

#include "CodeExpression.h"
#include "../identifier/CodeFunction.h"

using namespace std;

namespace AST {
	class CodeExpressionFunctionCall : public CodeExpression {
	private:
		CodeFunction *_function;
		vector<CodeExpression*> _parameters;
	public:
		CodeExpressionFunctionCall(CodeFunction *function) : _function(function) { };
		
		void addParameter(CodeExpression *expression) 
			{ _parameters.push_back(expression); }
		
		CodeFunction *getFunction()
			{ return _function; };
		
		auto getParameters() -> decltype(_parameters)
			{ return _parameters; };
		
		string code();
        
        virtual string toString(){ return "f:" + _function->getName() + "()"; }
	};
}

#endif

