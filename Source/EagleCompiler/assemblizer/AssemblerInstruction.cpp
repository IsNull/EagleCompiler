//
//  Assemblizer.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 10/17/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "AssemblerInstruction.h"


AdditionInstruction::AdditionInstruction(string op1, string op2){
	_op1 = op1;
	_op2 = op2;
}

string AdditionInstruction::getAssemblerCode(){
	//if we work without eax, op2 would be overwritten by the result
	string ret = "movl " + _op2 + ",%eax\n";
	return ret + "addl " + _op1 + ",%eax\n";
}

WriteToStandardOutputInstruction::WriteToStandardOutputInstruction(string op1) {
	_op1 = op1;
}

string WriteToStandardOutputInstruction::getAssemblerCode() {
	string ret;
	ret += "movl $" + std::to_string(_op1.size()) + ",%edx\n";
	ret += "movl $" + _op1 + ",%ecx\n";
	ret += "movl $1,%ebx\n";
	ret += "movl $4,%eax\n";
	return ret + "int $0x80\n";
}