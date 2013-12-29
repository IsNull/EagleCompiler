//
//  CodeTypeInteger32
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeTypeInteger32__
#define __EagleCompiler__CodeTypeInteger32__

#include <string.h>

using namespace std;

namespace AST {
	class CodeTypeInteger32 : public CodeType {
	private:
		
	public:
		string code();
	};
}

#endif

