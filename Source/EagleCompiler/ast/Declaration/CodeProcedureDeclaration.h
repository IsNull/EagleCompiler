//
//  CodeProcedureDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProcedureDeclaration__
#define __EagleCompiler__CodeProcedureDeclaration__

#include <string.h>

using namespace std;

namespace AST {
	class CodeProcedureDeclaration : public CodeDeclaration {
	private:
		
	public:
		string code();
	};
}

#endif

