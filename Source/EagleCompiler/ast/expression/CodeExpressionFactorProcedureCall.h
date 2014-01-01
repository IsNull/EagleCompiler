//
//  CodeExpressionFactorProcedureCall
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorProcedureCall__
#define __EagleCompiler__CodeExpressionFactorProcedureCall__

#include <string>

#include "CodeExpression.h"
#include "CodeExpressionFactor.h"
#include "../identifier/CodeProcedure.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorProcedureCall : public CodeExpressionFactor {
	private:
		CodeProcedure *_procedure;
		vector<CodeExpression> _parameters;

	public:
		CodeExpressionFactorProcedureCall(CodeProcedure *procedure) : _procedure(procedure) { };
		
		CodeProcedure *getProcedure() { return _procedure; };
		vector<CodeExpression>& getParameters() { return _parameters; };

		string code();
	};
}

#endif

