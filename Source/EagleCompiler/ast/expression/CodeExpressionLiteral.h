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
		CodeType *_type;
		string _value;
	public:
		CodeExpressionLiteral(CodeType *type, string value) : _type(type), _value(value) { };
		
		CodeType *getType() { return _type; };
		string getValue() { return _value; };

		string code();
        
        virtual string toString(){ return "CodeExpressionLiteral(" + _value + ")"; }
	};
}

#endif

