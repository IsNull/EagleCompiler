//
//  CodeExpression
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpression__
#define __EagleCompiler__CodeExpression__

#include <string>
#include <vector>

#include "CodeExpression.h"
#include "CodeExpressionStringConcatenation.h"

using namespace std;

namespace AST {
	class CodeExpressionExpression : CodeExpression{
	private:
		vector<CodeExpressionStringConcatenation> strings;
	public:
		vector<CodeExpressionStringConcatenation>& getStringConcatenationExpressions() { return strings; };
		
		string code();
	};
}

#endif

