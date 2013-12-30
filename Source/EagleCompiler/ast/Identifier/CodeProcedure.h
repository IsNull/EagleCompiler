//
//  CodeProcedure
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProcedure__
#define __EagleCompiler__CodeProcedure__

#include <string>

#include "CodeIdentifier.h"

using namespace std;

namespace AST {
	class CodeProcedure : public CodeIdentifier {
	private:
		
	public:
		string code();
	};
}

#endif

