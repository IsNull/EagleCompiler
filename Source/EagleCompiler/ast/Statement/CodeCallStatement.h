//
//  CodeCallStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeCallStatement__
#define __EagleCompiler__CodeCallStatement__

#include <string.h>

using namespace std;

namespace AST {
	class CodeCallStatement : public CodeStatement {
	private:
		
	public:
		string code();
	};
}

#endif

