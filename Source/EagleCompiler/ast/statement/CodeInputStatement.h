//
//  CodeInputStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeInputStatement__
#define __EagleCompiler__CodeInputStatement__

#include <string>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"

using namespace std;

namespace AST {
	class CodeInputStatement : public CodeStatement {
	private:
		CodeExpression *_expression;
	public:
		CodeInputStatement(CodeExpression *expression) : _expression(expression) { };
		
		CodeExpression *getExpression() { return _expression; };
		
		string code();
	};
}

#endif

