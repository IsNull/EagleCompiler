//
//  CodeStorageDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeStorageDeclaration__
#define __EagleCompiler__CodeStorageDeclaration__

#include <string.h>

using namespace std;

namespace AST {
	class CodeStorageDeclaration : public CodeDeclaration {
	private:
		
	public:
		string code();
	};
}

#endif

