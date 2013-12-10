//
//  StringVariable.h
//  EagleCompiler
//
//  Created by Samuel Stachelski on 21/11/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__StringVariable__
#define __EagleCompiler__StringVariable__

#include <string>
#include "Variable.h"

using namespace std;

namespace Assemblizer {

	class StringVariable: public Variable{
	private:
		string _init;
	public:
		StringVariable(string name, string init);
		string getAssemblerTypeString();
		string getInitialValue();
	};

}

#endif