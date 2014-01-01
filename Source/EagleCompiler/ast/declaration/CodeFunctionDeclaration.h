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

using namespace std;

namespace AST {
	class CodeFunctionDeclaration : public CodeDeclaration {
	private:
		CodeFunction *_function;
		vector<CodeParameter> _params;
		vector<CodeGlobalImport> _globalImps;
		vector<CodeStorageDeclaration> _localStoDecls;
		vector<CodeStatement> _statements;
		CodeStorageDeclaration *returnValue;
		
	public:
		CodeFunctionDeclaration(CodeFunction *function, CodeStorageDeclaration *returnValueDecl) : 
		CodeDeclaration(function), _function(function), returnValue(returnValueDecl) { };
		
		CodeFunction *getFunction() { return _function; };
		
		vector<CodeParameter>& getParameters() { return _params; };
		vector<CodeGlobalImport>& getPGlobalImports() { return _globalImps; };
		vector<CodeStorageDeclaration>& getLocalStorageDeclarations() { return _localStoDecls; };
		vector<CodeStatement>& getStatements() { return _statements; };
		CodeStorageDeclaration *getReturnValueDeclaration() { return returnValue; };
		
		string code();
	};
}

#endif

