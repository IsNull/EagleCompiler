//
//  CodeProgram
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProgram__
#define __EagleCompiler__CodeProgram__

#include <string.h>

using namespace std;

namespace AST {
	class CodeProgram : public CodeCodeObject {
	private:
		
	public:
		string code();
	};
}

#endif

