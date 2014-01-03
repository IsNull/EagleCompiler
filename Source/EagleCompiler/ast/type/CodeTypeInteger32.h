//
//  CodeTypeInteger32
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeTypeInteger32__
#define __EagleCompiler__CodeTypeInteger32__

#include <string>

#include "CodeType.h"

using namespace std;

namespace AST {
	class CodeTypeInteger32 : public CodeType {
    private:
        static CodeTypeInteger32* _instance;
	public:
		string code();
        static CodeTypeInteger32* getInstance();
	};
}

#endif

