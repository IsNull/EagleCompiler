//
//  CodeIfStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeIfStatement__
#define __EagleCompiler__CodeIfStatement__

#include <string>

#include "CodeStatement.h"

using namespace std;

namespace AST {
	class CodeIfStatement : public CodeStatement {
	private:
		
	public:
		string code();
	};
}

#endif

