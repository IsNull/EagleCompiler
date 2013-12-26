//
//  Assemblizer.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 10/17/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "AssemblerInstruction.h"

namespace Assemblizer {
	int tmpVariableCounter=0;
}

Assemblizer::ArithmeticInstruction::ArithmeticInstruction(string param1, string param2, string op){
	_param1 = param1;
	_param2 = param2;
	_operator = op;
}

string Assemblizer::ArithmeticInstruction::getAssemblerCode(){
	//if we work without eax, op2 would be overwritten by the result
	string ret = "mov eax," + _param2 + "\n";
	ret += _operator + " eax," + _param1 + "\n";
	
	//modulo is in assembler the same as division, but the result is stored in edx
	if(_operator == MODULO) {
		ret += "mov edx, eax\n";
	}
	return ret;
}

Assemblizer::Comparison::Comparison(string param1, string param2, string op){
	_param1 = param1;
	_param2 = param2;
	_operator = op;
}

string Assemblizer::Comparison::getAssemblerCode(){
	string ret = "mov eax," + _param2 + "\n";
	ret += "cmp eax," + _param1 + "\n";
	ret += "set" + _operator + " eax\n";
	
	return ret;
}

Assemblizer::BooleanCondition::BooleanCondition(string param1, string param2, string op){
	_param1 = param1;
	_param2 = param2;
	_operator = op;
}

string Assemblizer::BooleanCondition::getAssemblerCode(){
	int tmp=tmpVariableCounter++;
	string tmpLabelFalse = "_false" + tmp;
	string tmpLableEnd = "_end" + tmp;
	string ret;
	if(_operator == AND){
		ret += "cmp 0," + _param1 + "\n";
		ret += "je " + tmpLabelFalse + "\n";
		ret += "cmp 0," + _param2 + "\n";
		ret += "je " + tmpLabelFalse + "\n";
		ret += "mov eax,1\n";
		ret += "jmp " + tmpLableEnd + "\n";
		ret += tmpLabelFalse + ":\n";
		ret += "mov eax,0\n";
		ret += tmpLableEnd + ":\n";
	} else if(_operator == OR){
		string ret;
		ret += "cmp 0," + _param1 + "\n";
		ret += "jg " + tmpLabelFalse + "\n";
		ret += "cmp 0," + _param2 + "\n";
		ret += "jg " + tmpLabelFalse + "\n";
		ret += "mov eax,0\n";
		ret += "jmp " + tmpLableEnd + "\n";
		ret += tmpLabelFalse + ":\n";
		ret += "mov eax,1\n";
		ret += tmpLableEnd + ":\n";
	}
	
	return ret;
}

Assemblizer::WriteToStandardOutputInstruction::WriteToStandardOutputInstruction(string op1) {
	_op1 = op1;
}

string Assemblizer::WriteToStandardOutputInstruction::getAssemblerCode() {
	string ret;
	
	//write the variable itself
	ret += "mov edx," + std::to_string(_op1.size()) + "\n";
	ret += "mov ecx," + _op1 + "\n";
	ret += "mov ebx,1\n";
	ret += "mov eax,4\n";
	ret += "int 0x80\n";
	
	return ret;
}