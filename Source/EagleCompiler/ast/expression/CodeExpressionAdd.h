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
#include <utility>

#include "CodeExpressionRelation.h"

using namespace std;

namespace AST {
	class CodeExpressionMultiply;
	
	enum class ADDOPERATOR {
		PLUS,
		MINUS
	};
	
	class CodeExpressionAdd : public CodeExpressionRelation {
	private:
		vector<pair<ADDOPERATOR, CodeExpressionMultiply*>> _multiplys;
	public:
		
		void addExpression(ADDOPERATOR op, CodeExpressionMultiply *expression) 
			{ _multiplys.push_back(make_pair(op, expression)); }
		
		auto getMultiplyExpressions() -> decltype(_multiplys)
			{ return _multiplys; };
		
		string code();
	};
}

#endif

