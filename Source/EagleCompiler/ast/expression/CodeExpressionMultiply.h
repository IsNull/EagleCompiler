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
#include <utility>

#include "CodeExpressionAdd.h"

using namespace std;

namespace AST {
	class CodeExpressionFactor;

	enum class MULTIPLYOPERATOR {
		TIMES,
		DIV,
		MOD,
	};
	
	class CodeExpressionMultiply : public CodeExpressionAdd {
	private:
		vector<pair<MULTIPLYOPERATOR,CodeExpressionFactor*>> _factors;
	public:
		void addFactor(CodeExpressionFactor *factor, MULTIPLYOPERATOR op) 
			{ _factors.push_back(make_pair(op, factor)); }
		
		auto getFactors() -> decltype(_factors)
			{ return _factors; };
		
		string code();
	};
}

#endif

