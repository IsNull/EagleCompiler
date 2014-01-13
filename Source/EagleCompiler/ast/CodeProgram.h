//
//  CodeProgram
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProgram__
#define __EagleCompiler__CodeProgram__

#include <string>
#include <vector>

#include "CodeObject.h"
#include "CodeParameter.h"
#include "declaration/CodeDeclaration.h"
#include "statement/CodeStatement.h"

using namespace std;

namespace AST {
	class CodeProgram : public CodeObject {
	private:
		vector<CodeParameter*> _progParams;
		vector<CodeDeclaration*> _globalDecl;
		vector<CodeStatement*> _progStatements;
		
		
	public:
		static CodeVariable *tmp1,*tmp2;
		void addProgParam(CodeParameter *progParam)
			{ _progParams.push_back(progParam); }
			
		void addGlobalDecl(CodeDeclaration *globalDecl)
			{ _globalDecl.push_back(globalDecl); }
			
		void addProgStatement(CodeStatement *progStatement)
			{ _progStatements.push_back(progStatement); }
			
		auto getProgParams() -> decltype(_progParams)
			{ return _progParams; };
			
		auto getGlobalDecl() -> decltype(_globalDecl)
			{ return _globalDecl; };
			
		auto getProgStatements() -> decltype(_progStatements)
			{ return _progStatements; };
		
		string code();
        
        
        virtual string toString()const{ return "<CodeProgram>";}
	};
}

#endif

