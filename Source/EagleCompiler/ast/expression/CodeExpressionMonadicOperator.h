//
//  CodeExpressionMonadicOperator
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionMonadicOperator__
#define __EagleCompiler__CodeExpressionMonadicOperator__

#include <string>

#include "CodeExpression.h"
#include "CodeExpressionFactor.h"

using namespace std;

namespace AST {
	enum class MONADICOPERATOR {
		NOT,
		ADDOPR,
	};
	
	class CodeExpressionMonadicOperator : public CodeExpressionFactor {
	private:
		CodeExpressionFactor *_factor;
		MONADICOPERATOR _monadicOperator;
	public:
		CodeExpressionMonadicOperator(CodeExpressionFactor *factor, MONADICOPERATOR monadicOperator) :
			_factor(factor), _monadicOperator(monadicOperator) { };
		
		CodeExpressionFactor *getFactor() { return _factor; };
		MONADICOPERATOR getMonadicOperator() { return _monadicOperator; };
		
		string code();
	};
}

#endif

