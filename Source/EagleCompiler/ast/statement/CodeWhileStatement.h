//
//  CodeWhileStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeWhileStatement__
#define __EagleCompiler__CodeWhileStatement__

#include <string>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"
#include "../statement/CodeStatement.h"

using namespace std;

namespace AST {
	class CodeWhileStatement : public CodeStatement {
	private:
		CodeExpression *_condition;
		vector<CodeStatement *> _loopStatements;
	public:
		CodeWhileStatement(CodeExpression *condition) : _condition(condition) { };
		
		void addLoopStatement(CodeStatement *statement)
			{ _loopStatements.push_back(statement); }
		
		CodeExpression *getConditionExpression() { return _condition; };
		
		auto getLoopStatements() -> decltype(_loopStatements)
			{ return _loopStatements; };

		string code();
	};
}

#endif

