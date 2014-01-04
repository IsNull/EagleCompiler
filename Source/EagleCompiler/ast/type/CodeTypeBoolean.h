//
//  CodeTypeBoolean
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeTypeBoolean__
#define __EagleCompiler__CodeTypeBoolean__

#include <string>

#include "CodeType.h"

using namespace std;

namespace AST {
	class CodeTypeBoolean : public CodeType {
	private:
        static CodeTypeBoolean* _instance;
	public:
		string code();
        static CodeTypeBoolean* getInstance();
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeTypeBoolean& node) {
            stream << "CodeTypeBoolean";
            return stream;
        };
	};
}

#endif

