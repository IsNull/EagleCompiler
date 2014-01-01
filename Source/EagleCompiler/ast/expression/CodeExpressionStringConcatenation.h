//
//  CodeExpressionStringConcatenation
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionStringConcatenation__
#define __EagleCompiler__CodeExpressionStringConcatenation__

#include <string>

#include "CodeExpression.h"

using namespace std;

namespace AST {
	class CodeExpressionStringConcatenation : public CodeExpression {
	private:
		
	public:
		string code();
	};
}

#endif
