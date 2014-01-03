//
//  CodeProcedureCallStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProcedureCallStatement__
#define __EagleCompiler__CodeProcedureCallStatement__

#include <string>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"
#include "../identifier/CodeProcedure.h"

using namespace std;

namespace AST {
	class CodeProcedureCallStatement : public CodeStatement {
	private:
		CodeProcedure *_procedure;
		vector<CodeExpression *> _parameters;

	public:
		CodeProcedureCallStatement(CodeProcedure *procedure) : _procedure(procedure) { };
		
		void addParameterExpression(CodeExpression *parameter)
			{ _parameters.push_back(parameter); };
		
		CodeProcedure *getProcedure()
			{ return _procedure; };
			
		auto getParameters() -> decltype(_parameters)
			{ return _parameters; };

		string code();
	};
}

#endif

