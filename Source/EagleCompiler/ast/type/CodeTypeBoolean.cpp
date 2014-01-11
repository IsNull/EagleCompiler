//
//  CodeTypeBoolean.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeTypeBoolean.h"

using namespace std;
using namespace AST;

CodeTypeBoolean *CodeTypeBoolean::_instance = 0;

string CodeTypeBoolean::code() {
	return "dd";
}

CodeTypeBoolean* CodeTypeBoolean::getInstance()
{
    if(_instance == NULL)
        _instance = new CodeTypeBoolean();
    return _instance;
};