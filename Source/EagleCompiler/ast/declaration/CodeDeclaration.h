//
//  CodeDeclaration
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeDeclaration__
#define __EagleCompiler__CodeDeclaration__

#include <string>
#include "../identifier/CodeIdentifier.h"

using namespace std;

namespace AST {
	class CodeDeclaration {
	private:
		CodeIdentifier *_identifier;
	public:
		CodeDeclaration(CodeIdentifier *identifier) : _identifier(identifier) { };
		
		CodeIdentifier *getIdentifier() { return _identifier; };
		
		string code();
	};
}

#endif

