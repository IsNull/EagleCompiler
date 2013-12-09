//
//  Variable.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 21/11/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "Variable.h"

Assemblizer::Variable::Variable(string name) {
	_name = name;
}

Assemblizer::string Variable::getName() {
	return _name;
}