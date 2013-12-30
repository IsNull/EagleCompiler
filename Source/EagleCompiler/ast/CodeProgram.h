//
//  CodeProgram
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProgram__
#define __EagleCompiler__CodeProgram__

#include <string>

#include "CodeObject.h"

using namespace std;

namespace AST {
	class CodeProgram : public CodeObject {
	private:
		
	public:
		string code();
	};
}

#endif

