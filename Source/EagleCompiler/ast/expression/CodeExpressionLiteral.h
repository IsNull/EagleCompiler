//
//  CodeExpressionLiteral
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionLiteral__
#define __EagleCompiler__CodeExpressionLiteral__

#include <string>

#include "CodeExpression.h"
#include "../identifier/CodeVariable.h"
#include "../type/CodeType.h"

using namespace std;

namespace AST {
	class CodeExpressionLiteral : public CodeExpression {
	private:
		string _value;
		CodeVariable *_variable;
	public:
		CodeExpressionLiteral(CodeVariable *variable, string value) : 
			_value(value), _variable(variable) { };
		
		CodeVariable *getVariable() { return _variable; };
		string getValue() { return _value; };

		string code();
        
        virtual string toString(){ return "CodeExpressionLiteral('" + _value + "')"; }
	};
}

#endif

