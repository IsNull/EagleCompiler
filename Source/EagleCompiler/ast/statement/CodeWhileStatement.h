//
//  CodeWhileStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeWhileStatement__
#define __EagleCompiler__CodeWhileStatement__

#include <string>

#include "CodeStatement.h"

using namespace std;

namespace AST {
	class CodeWhileStatement : public CodeStatement {
	private:
		
	public:
		string code();
	};
}

#endif
