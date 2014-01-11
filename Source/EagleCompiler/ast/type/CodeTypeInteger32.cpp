//
//  CodeTypeInteger32.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeTypeInteger32.h"

using namespace std;
using namespace AST;

CodeTypeInteger32 *::CodeTypeInteger32::_instance = 0;

string CodeTypeInteger32::code() {
	return "dd";
};

CodeTypeInteger32* CodeTypeInteger32::getInstance()
{
    if(_instance == NULL)
        _instance = new CodeTypeInteger32();
        return _instance;
};

