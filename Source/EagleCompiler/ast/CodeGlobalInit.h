//
//  CodeGlobalInit
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeGlobalInit__
#define __EagleCompiler__CodeGlobalInit__

#include <string>

#include "CodeObject.h"
#include "identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeGlobalInit : public CodeObject {
	private:
		CodeVariable *_variable;
	public:
		CodeGlobalInit() : _variable(nullptr) { };
		CodeGlobalInit(CodeVariable *variable) : _variable(variable) { };
		
		CodeVariable *getVariable() { return _variable; };
		
		string code();
        
        
         virtual string toString() const { return "<CodeGlobalInit>";}
	};
}

#endif

