//
//  StringVariable.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 21/11/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "StringVariable.h"

Assemblizer::StringVariable::StringVariable(string name, string init) : Variable(name) {
	_init = init;
}
Assemblizer::string StringVariable::getAssemblerTypeString() {
	return ".ascii";
}
Assemblizer::string StringVariable::getInitialValue() {
	return "\"" + _init + "\"";
}