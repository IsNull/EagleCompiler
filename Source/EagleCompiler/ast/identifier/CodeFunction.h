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
#include "../type/CodeType.h"

using namespace std;

namespace AST {
	class CodeFunction : public CodeIdentifier {
	private:
		CodeType _type;
	public:
		CodeFunction(string name, CodeType type) : CodeIdentifier(name), _type(type) { };
		
		CodeType getType() { return _type; };

		string code();
	};
}

#endif

