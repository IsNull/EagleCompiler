//
//  CodeExpressionInitializeVariable
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionInitializeVariable__
#define __EagleCompiler__CodeExpressionInitializeVariable__

#include <string>

#include "CodeExpression.h"

using namespace std;

namespace AST {
	
	//forward declaration
	class CodeVariable;
	
	class CodeExpressionInitializeVariable : public CodeExpression {
	private:
		CodeVariable *_variable;
	public:
		CodeExpressionInitializeVariable(CodeVariable *variable) : _variable(variable) { };
		
		CodeVariable *getVariable() { return _variable; };
		
		string code();
	};
}

#endif

