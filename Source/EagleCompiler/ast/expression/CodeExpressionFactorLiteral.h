//
//  CodeExpressionFactorLiteral
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorLiteral__
#define __EagleCompiler__CodeExpressionFactorLiteral__

#include <string>

#include "CodeExpressionFactor.h"
#include "../identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorLiteral : public CodeExpressionFactor {
	private:
		CodeType *_type;
		string _value;
	public:
		CodeExpressionFactorLiteral(CodeType *type, string value) : _type(type), _value(value) { };
		
		CodeType *getType() { return _type; };
		string getValue() { return _value; };

		string code();
	};
}

#endif

