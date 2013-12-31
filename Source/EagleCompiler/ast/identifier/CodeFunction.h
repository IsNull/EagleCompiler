//
//  CodeFunction
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeFunction__
#define __EagleCompiler__CodeFunction__

#include <string>

#include "CodeIdentifier.h"

using namespace std;

namespace AST {
	class CodeFunction : public CodeIdentifier {
	private:
		
	public:
		string code();
	};
}

#endif

