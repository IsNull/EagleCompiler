//
//  CodeExpressionAdd
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionAdd__
#define __EagleCompiler__CodeExpressionAdd__

#include <string.h>

using namespace std;

namespace AST {
	class CodeExpressionAdd : public CodeExpression {
	private:
		
	public:
		string code();
	};
}

#endif

