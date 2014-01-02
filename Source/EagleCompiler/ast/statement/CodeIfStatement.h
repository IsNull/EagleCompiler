//
//  CodeIfStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeIfStatement__
#define __EagleCompiler__CodeIfStatement__

#include <string>
#include <vector>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"
#include "../statement/CodeStatement.h"

using namespace std;

namespace AST {
	class CodeIfStatement : public CodeStatement {
	private:
		CodeExpression *_condition;
		vector<CodeStatement*> _ifStatements;
		vector<CodeStatement*> _elseStatements;
	public:
		CodeIfStatement(CodeExpression *condition) : _condition(condition) { };
		
		CodeExpression *getConditionExpression() 
			{ return _condition; };
			
		auto getIfStatements() -> decltype(_ifStatements)
			{ return _ifStatements; };
			
		auto getElseStatements() -> decltype(_elseStatements)
			{ return _elseStatements; };

		string code();
	};
}

#endif

