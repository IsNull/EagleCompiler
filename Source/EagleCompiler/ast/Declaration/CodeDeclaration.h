//
//  CodeDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeDeclaration__
#define __EagleCompiler__CodeDeclaration__

#include <string.h>

using namespace std;

namespace AST {
	class CodeDeclaration : public CodeDeclaration {
	private:
		
	public:
		string code();
	};
}

#endif

