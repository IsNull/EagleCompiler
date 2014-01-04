//
//  CodeExpressionUnaryExpression
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionUnaryExpression__
#define __EagleCompiler__CodeExpressionUnaryExpression__

#include <string>

#include "CodeExpression.h"

using namespace std;

namespace AST {	
	enum class UNARYOPERATOR {
		NOT,
		NEGATIVE,
	};
	
	class CodeExpressionUnaryExpression : public CodeExpression {
	private:
		CodeExpression *_expression;
		UNARYOPERATOR _unaryOperator;
	public:
		CodeExpressionUnaryExpression(CodeExpression *factor, UNARYOPERATOR unaryOperator) :
			_expression(factor), _unaryOperator(unaryOperator) { };
		
		CodeExpression *getExpression() 
			{ return _expression; };
			
		UNARYOPERATOR getMonadicOperator() 
			{ return _unaryOperator; };
		
		string code();
	};
}

#endif

