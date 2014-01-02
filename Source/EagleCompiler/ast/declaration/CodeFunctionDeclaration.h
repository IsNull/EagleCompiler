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
		vector<CodeParameter*> _params;
		vector<CodeGlobalImport*> _globalImps;
		vector<CodeStorageDeclaration*> _localStoDecls;
		vector<CodeStatement*> _statements;
		CodeStorageDeclaration *returnValue;
		
	public:
		CodeFunctionDeclaration(CodeFunction *function) : 
			CodeDeclaration(function), _function(function) { };
		
		void addParam(CodeParameter *param)
			{ _params.push_back(param); }
			
		void addGlobalImport(CodeGlobalImport *import)
			{ _globalImps.push_back(import); }
			
		void addLocalStoDecl(CodeStorageDeclaration *stoDecl)
			{ _localStoDecls.push_back(stoDecl); }
			
		void addStatement(CodeStatement *statement)
			{ _statements.push_back(statement); }
			
		CodeFunction *getFunction() { return _function; };
		
		auto getParameters() -> decltype(_params)
			{ return _params; };
			
		auto getPGlobalImports() -> decltype(_globalImps)
			{ return _globalImps; };
			
		auto getLocalStorageDeclarations() -> decltype(_localStoDecls)
			{ return _localStoDecls; };
			
		auto getStatements() -> decltype(_statements)
			{ return _statements; };
		
		string code();
	};
}

#endif

