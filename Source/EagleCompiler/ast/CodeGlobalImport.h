//
//  CodeGlobalImport
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-29.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeGlobalImport__
#define __EagleCompiler__CodeGlobalImport__

#include <string.h>

using namespace std;

namespace AST {
	class CodeGlobalImport : public CodeCodeObject {
	private:
		
	public:
		string code();
	};
}

#endif

