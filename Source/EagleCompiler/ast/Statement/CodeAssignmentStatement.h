//
//  CodeAssignmentStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeAssignmentStatement__
#define __EagleCompiler__CodeAssignmentStatement__

#include <string.h>

using namespace std;

namespace AST {
	class CodeAssignmentStatement : public CodeStatement {
	private:
		
	public:
		string code();
	};
}

#endif

