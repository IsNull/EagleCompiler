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
#include <vector>
#include <utility>

#include "CodeExpression.h"

using namespace std;

namespace AST {
	class CodeExpressionBoolean;
	
	class CodeExpressionStringConcatenation : public CodeExpression {
	private:
		vector<CodeExpressionBoolean*> _booleanTerms;
	public:
		void addExpression(CodeExpressionBoolean *expression)
			{ _booleanTerms.push_back(expression); }
		
		auto getBooleanTermExpressions() -> decltype(_booleanTerms) 
			{ return _booleanTerms; };
		
		string code();
	};
}

#endif

