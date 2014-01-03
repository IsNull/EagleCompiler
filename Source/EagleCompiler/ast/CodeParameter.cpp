//
//  CodeParameter.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeParameter.h"

using namespace std;

string AST::CodeParameter::code() {
	return "[" + FlowModeString[_flowmode] + "|" + MechModeString[_mechmode] + "|" + ChangeModeString[_changemode] + "#" + _variable->code() + "]";
}

