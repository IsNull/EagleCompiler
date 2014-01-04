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

#include "../CodeObject.h"

using namespace std;

namespace AST {
	class CodeType : public CodeObject {
	private:
		
	public:
        
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeType& node) {
            stream << "CodeType";
            return stream;
        };
	};
}

#endif

