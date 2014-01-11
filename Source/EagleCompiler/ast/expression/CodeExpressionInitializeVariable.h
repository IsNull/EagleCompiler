//
//  CodeExpressionInitializeVariable
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeExpressionInitializeVariable__
#define __EagleCompiler__CodeExpressionInitializeVariable__

#include <string>

#include "CodeExpression.h"
#include "CodeExpressionVariable.h"

using namespace std;

namespace AST {
	
	//forward declaration
    class CodeVariable;
	
	class CodeExpressionInitializeVariable : public CodeExpressionVariable {

	public:
		CodeExpressionInitializeVariable(CodeVariable *variable)
        : CodeExpressionVariable(variable) { };
				
		string code();
        
        virtual string toString(){
            return "init:var(" + getVariable()->toString() + ")";
        }
	};
}

#endif

