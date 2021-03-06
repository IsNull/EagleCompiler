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

#include "../CodeObject.h"
#include "../type/CodeType.h"

using namespace std;

namespace AST {
	class CodeExpression : public CodeObject{
	private:

	public:
        
        virtual CodeType getType()=0;
        
        virtual string toString(){ return "<CodeExpression>"; }
	};

}

#endif

