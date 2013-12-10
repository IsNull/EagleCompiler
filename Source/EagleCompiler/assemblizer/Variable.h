//
//  Variable.h
//  EagleCompiler
//
//  Created by Samuel Stachelski on 21/11/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__Variable__
#define __EagleCompiler__Variable__

#include <string>

using namespace std;

namespace Assemblizer {
	
	class Variable{
	private:
		string _name;
	public:
		Variable(string name);
		string getName();
		
		virtual string getAssemblerTypeString() = 0;
		virtual string getInitialValue() = 0;
	};
	
}

#endif