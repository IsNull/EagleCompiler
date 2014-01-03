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
#include <vector>
#include <utility>

#include "CodeExpressionStringConcatenation.h"

using namespace std;

namespace AST {
	class CodeExpressionRelation;
	
	enum class BOOLEANOPERATOR {
		AND,
		OR,
		CAND,
		COR
	};
	
	class CodeExpressionBoolean : public CodeExpressionStringConcatenation {
	private:
		vector<pair<BOOLEANOPERATOR,CodeExpressionRelation*>> _relations;
	public:
		//On the first element, op will be ignored
		void addExpression(BOOLEANOPERATOR op, CodeExpressionRelation *expression) 
			{ _relations.push_back(make_pair(op, expression)); }
		
		auto getRelationExpressions() -> decltype(_relations)
			{ return _relations; };
		
		string code();
	};
}

#endif

