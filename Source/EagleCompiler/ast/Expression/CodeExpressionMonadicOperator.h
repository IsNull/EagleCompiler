//
//  CodeExpressionMonadicOperator
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionMonadicOperator__
#define __EagleCompiler__CodeExpressionMonadicOperator__

#include <string.h>

using namespace std;

namespace AST {
	class CodeExpressionMonadicOperator : public CodeExpression {
	private:
		
	public:
		string code();
	};
}

#endif

