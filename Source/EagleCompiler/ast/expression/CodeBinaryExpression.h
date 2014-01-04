//
//  CodeBinaryExpression
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeBinaryExpression__
#define __EagleCompiler__CodeBinaryExpression__

#include <string>
#include <vector>

#include "CodeExpression.h"

using namespace std;

namespace AST {
	enum class BINARYOPERATOR {
		TIMES,
		DIV,
		MOD,
		PLUS,
		MINUS,
		LESS,
		GREATER_EQ,
		EQUAL,
		NOT_EQ,
		GREATER,
		LESS_EQ,
		COND_AND,
		COND_OR,
		STR_CONCAT,
	};
	
	class CodeBinaryExpression : public CodeExpression{
	private:
		CodeExpression *_left;
		BINARYOPERATOR _binaryOperator;
		CodeExpression *_right;
	public:
		CodeBinaryExpression(CodeExpression *left, BINARYOPERATOR binaryOperator, CodeExpression *right) : 
			_left(left), _binaryOperator(binaryOperator), _right(right) { };
			
		CodeExpression *getLeftExpression() { return _left; };
		BINARYOPERATOR getBinaryOperator() { return _binaryOperator; };
		CodeExpression *getRightExpression() { return _right; };
		
		string code();
	};
}

#endif

