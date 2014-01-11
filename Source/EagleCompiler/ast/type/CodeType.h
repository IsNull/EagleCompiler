//
//  CodeType
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeType__
#define __EagleCompiler__CodeType__

#include <string>

using namespace std;

namespace AST {
	enum class CodeType {
        UNKNOWN,
        
		//VOID,
		INT32,
		BOOL,
		STRING
	};
	
	namespace STRING {
		const int BUFFER_LEN = 256;
	}

}

#endif

