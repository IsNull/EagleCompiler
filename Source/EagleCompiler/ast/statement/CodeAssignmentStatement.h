//
//  CodeAssignmentStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeAssignmentStatement__
#define __EagleCompiler__CodeAssignmentStatement__

#include <string>

#include "CodeStatement.h"
#include "../expression/CodeExpression.h"

using namespace std;

namespace AST {
	class CodeAssignmentStatement : public CodeStatement {
	private:
		CodeExpression *_lvalue;
		CodeExpression *_rvalue;
	public:
		CodeAssignmentStatement(CodeExpression *lvalue, CodeExpression *rvalue) : 
			_lvalue(lvalue), _rvalue(rvalue) { };
		
		CodeExpression *getLValue() { return _lvalue; };
		CodeExpression *getRValue() { return _rvalue; };
		
        virtual string toString(){ return _lvalue->toString() + " := " + _rvalue->toString(); }
        
		string code();
	};
}

#endif

