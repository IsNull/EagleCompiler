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
		vector<CodeParameter> progParams;
		vector<CodeDeclaration> globalDecl;
		vector<CodeStatement> progStatements;
		
	public:
		string code();
		vector<CodeParameter>& getProgParams() { return progParams; };
		vector<CodeDeclaration>& getGlobalDecl() { return globalDecl; };
		vector<CodeStatement>& getProgStatements() { return progStatements; };
	};
}

#endif

