//
//  CodeFunctionDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeFunctionDeclaration__
#define __EagleCompiler__CodeFunctionDeclaration__

#include <string.h>

using namespace std;

namespace AST {
	class CodeFunctionDeclaration : public CodeDeclaration {
	private:
		
	public:
		string code();
	};
}

#endif

