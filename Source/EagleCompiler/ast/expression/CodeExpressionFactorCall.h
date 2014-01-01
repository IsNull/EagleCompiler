//
//  CodeExpressionFactorCall
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionFactorCall__
#define __EagleCompiler__CodeExpressionFactorCall__

#include <string>

#include "CodeExpression.h"

using namespace std;

namespace AST {
	class CodeExpressionFactorCall : public CodeExpression {
	private:
		
	public:
		string code();
	};
}

#endif
