//
//  CodeExpressionBoolean
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionBoolean__
#define __EagleCompiler__CodeExpressionBoolean__

#include <string>

#include "CodeExpression.h"

using namespace std;

namespace AST {
	class CodeExpressionBoolean : public CodeExpression {
	private:
		
	public:
		string code();
	};
}

#endif
