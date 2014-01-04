//
//  CodeObject
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeObject__
#define __EagleCompiler__CodeObject__

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace AST {
	class CodeObject {
	private:
		
	public:
		virtual string code() = 0;
        virtual string toString() const { return "<CodeObject>";}
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeObject& node) {
            stream << node.toString();
            return stream;
        };
	};
}

#endif

