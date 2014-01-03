//
//  CodeProcedureDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProcedureDeclaration__
#define __EagleCompiler__CodeProcedureDeclaration__

#include <string>
#include <vector>

#include "CodeDeclaration.h"
#include "CodeStorageDeclaration.h"
#include "../CodeParameter.h"
#include "../CodeGlobalImport.h"
#include "../identifier/CodeProcedure.h"
#include "../statement/CodeStatement.h"

using namespace std;

namespace AST {
	class CodeProcedureDeclaration : public CodeDeclaration {
	private:
		CodeProcedure *_procedure;
		vector<CodeParameter*> _params;
		vector<CodeGlobalImport*> _globalImps;
		vector<CodeStorageDeclaration*> _localStoDecls;
		vector<CodeStatement*> _statements;
		
	public:
		CodeProcedureDeclaration(CodeProcedure *procedure) : 
			CodeDeclaration(procedure), _procedure(procedure) { };
		
		void addParam(CodeParameter *param)
			{ _params.push_back(param); }
			
		void addGlobalImport(CodeGlobalImport *import)
			{ _globalImps.push_back(import); }
			
		void addLocalStoDecl(CodeStorageDeclaration *stoDecl)
			{ _localStoDecls.push_back(stoDecl); }
			
		void addStatement(CodeStatement *statement)
			{ _statements.push_back(statement); }
			
		CodeProcedure *getProcedure() { return _procedure; };
		
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

