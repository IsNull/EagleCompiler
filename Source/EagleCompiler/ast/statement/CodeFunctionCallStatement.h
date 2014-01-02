//
//  CodeFunctionCallStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeFunctionCallStatement__
#define __EagleCompiler__CodeFunctionCallStatement__

#include <string>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"
#include "../identifier/CodeFunction.h"

using namespace std;

namespace AST {
	class CodeFunctionCallStatement : public CodeStatement {
	private:
		CodeFunction *_function;
		vector<CodeExpression*> _parameters;
	public:
		CodeFunctionCallStatement(CodeFunction *function) : _function(function) { };
		
		void addParameterExpression(CodeExpression *parameter)
			{ _parameters.push_back(parameter); };
		
		CodeFunction *getFunction()
			{ return _function; };
		
		auto getParameters() -> decltype(_parameters) 
			{ return _parameters; };
		
		string code();
	};
}

#endif

