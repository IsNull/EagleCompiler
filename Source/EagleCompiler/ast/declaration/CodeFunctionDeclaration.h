//
//  CodeFunctionDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeFunctionDeclaration__
#define __EagleCompiler__CodeFunctionDeclaration__

#include <string>
#include <vector>

#include "CodeDeclaration.h"
#include "CodeStorageDeclaration.h"
#include "../CodeParameter.h"
#include "../CodeGlobalImport.h"
#include "../identifier/CodeFunction.h"
#include "../statement/CodeStatement.h"
#include "CodeProcedureDeclaration.h"

using namespace std;

namespace AST {
	class CodeFunctionDeclaration : public CodeInvokableDeclaration {
	protected:
		CodeFunction *_function;
        CodeStorageDeclaration *_returnValue;
		
	public:
		CodeFunctionDeclaration(CodeFunction *function, CodeStorageDeclaration *returnValue) :
			CodeInvokableDeclaration(function), _function(function), _returnValue(returnValue) { };
					
		CodeFunction *getFunction() { return _function; };
		
		CodeStorageDeclaration *getReturnDeclaration() { return _returnValue; };
		
		string code();
        
        virtual string toString()const{ return "<CodeFunctionDeclaration>";}
	};
}

#endif

