//
//  CodeTypeString
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeTypeString__
#define __EagleCompiler__CodeTypeString__

#include <string>

#include "CodeType.h"

using namespace std;

namespace AST {
	class CodeTypeString : public CodeType {
	private:
        static CodeTypeString* _instance;
	public:
		static const int BUFFERLEN = 256;
		string code();
        static CodeTypeString* getInstance();
        
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeTypeString& node) {
            stream << "CodeTypeString";
            return stream;
        };
	};
}

#endif

