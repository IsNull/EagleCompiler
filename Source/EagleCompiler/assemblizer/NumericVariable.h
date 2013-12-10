//
//  NumericVariable.h
//  EagleCompiler
//
//  Created by Samuel Stachelski on 21/11/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__NumericVariable__
#define __EagleCompiler__NumericVariable__

#include <string>
#include "Variable.h"

using namespace std;

namespace Assemblizer {

	class NumericVariable : public Variable{
	private:
		int32_t _init;
	public:
		NumericVariable(string name, int32_t init);
		string getAssemblerTypeString();
		string getInitialValue();
	};
}

#endif