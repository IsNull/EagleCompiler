//
//  CodeSkipStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeSkipStatement__
#define __EagleCompiler__CodeSkipStatement__

#include <string>

#include "CodeStatement.h"

using namespace std;

namespace AST {
	class CodeSkipStatement : public CodeStatement{
	private:
		
	public:
		string code();
	};
}

#endif

