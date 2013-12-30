//
//  CodeGlobalInit
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeGlobalInit__
#define __EagleCompiler__CodeGlobalInit__

#include <string>

#include "CodeObject.h"

using namespace std;

namespace AST {
	class CodeGlobalInit : public CodeObject {
	private:
		
	public:
		string code();
	};
}

#endif

