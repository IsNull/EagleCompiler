//
//  CodeExpressionVariable
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionVariable__
#define __EagleCompiler__CodeExpressionVariable__

#include <string>

#include "CodeExpression.h"
#include "../identifier/CodeVariable.h"

using namespace std;

namespace AST {
	
	
	class CodeExpressionVariable : public CodeExpression {
	private:
		CodeVariable *_variable;
	public:
		CodeExpressionVariable(CodeVariable *variable) : _variable(variable) { };
		
		CodeVariable *getVariable() { return _variable; };
		
		string code();
        
        virtual string toString(){
            return "variable(" + _variable->toString() + ")";
        }

	};
}

#endif

