//
//  CodeTypeString.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeTypeString.h"

using namespace std;
using namespace AST;

CodeTypeString *CodeTypeString::_instance = 0;

string CodeTypeString::code() {
	return "string";
}


CodeTypeString* CodeTypeString::getInstance(){
    if(_instance == NULL){
        _instance = new CodeTypeString();
    }
    return _instance;
}