//
//  CodeStorageDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeStorageDeclaration__
#define __EagleCompiler__CodeStorageDeclaration__

#include <string>

#include "CodeDeclaration.h"
#include "../identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeStorageDeclaration : public CodeDeclaration {
	private:
		CodeVariable *_variable;
		CHANGEMODE _changeMode;
	public:
		CodeStorageDeclaration(CHANGEMODE changeMode, CodeVariable *variable) : 
		CodeDeclaration(variable), _variable(variable), _changeMode(changeMode) { };
		
		CHANGEMODE getChangeMode() { return _changeMode; };
		CodeVariable *getVariable() { return _variable; };
		
		string code();
        
        virtual string toString(){ return "<CodeStorageDeclaration>"; }

	};
}

#endif

