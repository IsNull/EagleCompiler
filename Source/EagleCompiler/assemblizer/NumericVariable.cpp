//
//  NumericVariable.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 21/11/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "NumericVariable.h"

Assemblizer::NumericVariable::NumericVariable(string name, int32_t init) : Variable(name) {
	_init = init;
}
Assemblizer::string NumericVariable::getAssemblerTypeString() {
	return ".word";
}
Assemblizer::string NumericVariable::getInitialValue() {
	return std::to_string(_init);
}