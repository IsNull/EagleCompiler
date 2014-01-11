//
//  CodeVariable.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeVariable.h"

using namespace std;

namespace AST {
	map<FLOWMODE, string> FlowModeString = { 
		{ FLOWMODE::EMPTY, "flowmode::empty" },  
		{ FLOWMODE::IN, "flowmode::in" }, 
		{ FLOWMODE::OUT, "flowmode::out" }, 
		{ FLOWMODE::INOUT, "flowmode::inout" } 
	};
		map<MECHMODE, string> MechModeString = { 
		{ MECHMODE::EMPTY, "mechmode::empty" },  
		{ MECHMODE::COPY, "mechmode::copy" }, 
		{ MECHMODE::REF, "mechmode::out" } 
	};
	map<CHANGEMODE, string> ChangeModeString = { 
		{ CHANGEMODE::EMPTY, "changemode::empty" },  
		{ CHANGEMODE::CONST, "changemode::const" }, 
		{ CHANGEMODE::VAR, "changemode::var" } 
	};
}

string AST::CodeVariable::code() {
	return "[ebp+" + to_string(_stackOffset) +"]";
}

