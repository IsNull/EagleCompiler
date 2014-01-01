//
//  CodeExpressionAdd
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionAdd__
#define __EagleCompiler__CodeExpressionAdd__

#include <string>
#include <vector>

#include "CodeExpression.h"
#include "CodeExpressionMultiply.h"

using namespace std;

namespace AST {
	class CodeExpressionAdd : public CodeExpression {
	private:
		vector<CodeExpressionMultiply> multiplys;
	public:
		vector<CodeExpressionMultiply>& getMultiplyExpressions() { return multiplys; };
		
		string code();
	};
}

#endif

