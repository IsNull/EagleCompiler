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
		vector<CodeParameter> _params;
		vector<CodeGlobalImport> _globalImps;
		vector<CodeStorageDeclaration> _localStoDecls;
		vector<CodeStatement> _statements;
		
	public:
		CodeProcedureDeclaration(CodeProcedure *procedure) : 
			CodeDeclaration(procedure), _procedure(procedure) { };
		
		CodeProcedure *getProcedure() { return _procedure; };
		
		vector<CodeParameter>& getParameters() { return _params; };
		vector<CodeGlobalImport>& getPGlobalImports() { return _globalImps; };
		vector<CodeStorageDeclaration>& getLocalStorageDeclarations() { return _localStoDecls; };
		vector<CodeStatement>& getStatements() { return _statements; };

		string code();
	};
}

#endif

