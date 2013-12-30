//
//  CodeVariable
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeVariable__
#define __EagleCompiler__CodeVariable__

#include <string>

#include "CodeIdentifier.h"

using namespace std;

namespace AST {
	class CodeVariable : public CodeIdentifier {
	private:
		
	public:
		string code();
	};
}

#endif

