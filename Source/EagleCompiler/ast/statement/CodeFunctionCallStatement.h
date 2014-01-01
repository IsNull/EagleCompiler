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
		vector<CodeExpression> _parameters;
	public:
		CodeFunctionCallStatement(CodeFunction *function) : _function(function) { };
		
		CodeFunction *getFunction() { return _function; };
		vector<CodeExpression>& getParameters() { return _parameters; };
		
		string code();
	};
}

#endif

