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
	string ret = "mov eax," + _op2 + "\n";
	return ret + "add eax," + _op1 + "\n";
}

WriteToStandardOutputInstruction::WriteToStandardOutputInstruction(string op1) {
	_op1 = op1;
}

string WriteToStandardOutputInstruction::getAssemblerCode() {
	string ret;
	
	//write the variable itself
	ret += "mov edx," + std::to_string(_op1.size()) + "\n";
	ret += "mov ecx," + _op1 + "\n";
	ret += "mov ebx,1\n";
	ret += "mov eax,4\n";
	ret += "int 0x80\n";
	
	return ret;
}