//
//  CodeExpressionRelation
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionRelation__
#define __EagleCompiler__CodeExpressionRelation__

#include <string>
#include <vector>

#include "CodeExpressionBoolean.h"

using namespace std;

namespace AST {
	class CodeExpressionAdd;
	
	enum class RELATIONOPERATOR {
		EQ,
		NE,
		GE,
		GT,
		LE,
		LT
	};
	
	class CodeExpressionRelation : public CodeExpressionBoolean {
	private:
		CodeExpressionAdd *_left;
		RELATIONOPERATOR _op;
		CodeExpressionAdd *_right;
	public:
		CodeExpressionRelation(){};
		CodeExpressionRelation(CodeExpressionAdd *left, RELATIONOPERATOR op, CodeExpressionAdd *right) :
			_left(left), _op(op), _right(right) { };
		
		CodeExpressionAdd * getLeftExpressions()
			{ return _left; };
			
		CodeExpressionAdd * getRightExpressions()
			{ return _right; };
			
		RELATIONOPERATOR getOperator()
			{ return _op; };
		
		string code();
	};
}

#endif

