//
//  CodeExpressionMultiply
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionMultiply__
#define __EagleCompiler__CodeExpressionMultiply__

#include <string.h>

using namespace std;

namespace AST {
	class CodeExpressionMultiply : public CodeExpression {
	private:
		
	public:
		string code();
	};
}

#endif

