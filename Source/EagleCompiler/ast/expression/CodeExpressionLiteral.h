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
#include <vector>

#include "CodeExpression.h"
#include "../identifier/CodeVariable.h"
#include "../type/CodeType.h"

using namespace std;

namespace AST {
	class CodeExpressionLiteral : public CodeExpression {
	private:
		string _value;
		CodeVariable *_variable;
		static vector<CodeExpressionLiteral*> literals;
	public:
		CodeExpressionLiteral(CodeVariable *variable, string value) : 
			_value(value), _variable(variable) { CodeExpressionLiteral::literals.push_back(this); };
		
		CodeVariable *getVariable() { return _variable; };
		string getValue() { return _value; };

		string code();
        
        virtual CodeType getType() {
            return _variable->getType();
        };
        
        virtual string toString(){ return "CodeExpressionLiteral('" + _value + "')"; }
        
        static auto getAllLiterals() -> decltype(CodeExpressionLiteral::literals)
			{ return CodeExpressionLiteral::literals; };
	};
}

#endif

