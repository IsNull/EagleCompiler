//
//  CodeStatement
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeStatement__
#define __EagleCompiler__CodeStatement__

#include <string>

#include "../CodeObject.h"

using namespace std;

namespace AST {
	class CodeStatement : public CodeObject{
	private:
		
	public:
        virtual string toString(){ return "CodeStatement"; }
	};
}

#endif

