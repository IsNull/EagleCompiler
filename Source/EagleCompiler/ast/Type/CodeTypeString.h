//
//  CodeTypeString
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeTypeString__
#define __EagleCompiler__CodeTypeString__

#include <string.h>

using namespace std;

namespace AST {
	class CodeTypeString : public CodeType {
	private:
		
	public:
		string code();
	};
}

#endif

