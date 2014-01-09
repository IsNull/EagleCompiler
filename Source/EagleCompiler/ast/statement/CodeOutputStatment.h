//
//  CodeOutputStatment
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeOutputStatment__
#define __EagleCompiler__CodeOutputStatment__

#include <string>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"

using namespace std;

namespace AST {
	class CodeOutputStatment : public CodeStatement {
	private:
		CodeExpression *_expression;
	public:
		CodeOutputStatment(CodeExpression *expression) : _expression(expression) { };
		
		CodeExpression *getExpression() { return _expression; };
		
		string code();
        
        
        virtual string toString(){ return "output " + _expression->toString(); }
	};
}

#endif

