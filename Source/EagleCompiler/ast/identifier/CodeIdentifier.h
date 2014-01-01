//
//  CodeIdentifier
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeIdentifier__
#define __EagleCompiler__CodeIdentifier__

#include <string>

using namespace std;

namespace AST {
	class CodeIdentifier {
	private:
		string _name;
	public:
		CodeIdentifier(string name) : _name(name) { };
		
		string getName() { return _name; };
		
		string code();
	};
}

#endif

