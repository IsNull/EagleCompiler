//
//  CodeStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeStatement__
#define __EagleCompiler__CodeStatement__

#include <string.h>

using namespace std;

namespace AST {
	class CodeStatement : public CodeStatement {
	private:
		
	public:
		string code();
	};
}

#endif

