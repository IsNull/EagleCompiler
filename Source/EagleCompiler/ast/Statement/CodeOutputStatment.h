//
//  CodeOutputStatment
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeOutputStatment__
#define __EagleCompiler__CodeOutputStatment__

#include <string.h>

using namespace std;

namespace AST {
	class CodeOutputStatment : public CodeStatement {
	private:
		
	public:
		string code();
	};
}

#endif

