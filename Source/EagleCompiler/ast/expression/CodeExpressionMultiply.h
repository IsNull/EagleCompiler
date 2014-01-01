//
//  CodeExpressionMultiply
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionMultiply__
#define __EagleCompiler__CodeExpressionMultiply__

#include <string>
#include <vector>

#include "CodeExpression.h"
#include "CodeExpressionFactor.h"

using namespace std;

namespace AST {
	class CodeExpressionMultiply : public CodeExpression {
	private:
		vector<CodeExpressionFactor> factors;
	public:
		vector<CodeExpressionFactor>& getFactors() { return factors; };
		
		string code();
	};
}

#endif

