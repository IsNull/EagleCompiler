//
//  CodeObject
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeObject__
#define __EagleCompiler__CodeObject__

#include <string>

using namespace std;

namespace AST {
	class CodeObject {
	private:
		
	public:
		virtual string code() = 0;
	};
}

#endif

