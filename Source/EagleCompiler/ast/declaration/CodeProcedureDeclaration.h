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
    	
    class CodeInvokableDeclaration : public CodeDeclaration{
	protected:
        vector<CodeParameter*> _params;
        vector<CodeGlobalImport*> _globalImps;
        vector<CodeStorageDeclaration*> _localStoDecls;
        vector<CodeStatement*> _statements;
	public:
        
        CodeInvokableDeclaration(CodeIdentifier *identifier)
            : CodeDeclaration(identifier) { }
        
		void addParam(CodeParameter *param)
        { _params.push_back(param); }
        
		void addGlobalImport(CodeGlobalImport *import)
        { _globalImps.push_back(import); }
        
		void addLocalStoDecl(CodeStorageDeclaration *stoDecl)
        { _localStoDecls.push_back(stoDecl); }
        
		void addStatement(CodeStatement *statement)
        { _statements.push_back(statement); }
        
        
        auto getParameters() -> decltype(_params)
        { return _params; };
        
		auto getPGlobalImports() -> decltype(_globalImps)
        { return _globalImps; };
        
		auto getLocalStorageDeclarations() -> decltype(_localStoDecls)
        { return _localStoDecls; };
        
		auto getStatements() -> decltype(_statements)
        { return _statements; };

        
        virtual string toString()const{ return "<CodeInvokableDeclaration>";}
	};
    
        
	class CodeProcedureDeclaration : public CodeInvokableDeclaration {
	private:
		CodeProcedure *_procedure;
		
	public:
		CodeProcedureDeclaration(CodeProcedure *procedure) : 
			CodeInvokableDeclaration(procedure), _procedure(procedure) { _procedure->setDeclaration(this); };
		
		CodeProcedure *getProcedure() { return _procedure; };
	
		string code();
        
      
        virtual string toString(){ return "<CodeProcedureDeclaration>"; }
	};
}

#endif

