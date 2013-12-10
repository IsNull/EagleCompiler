//
//  Assemblizer.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 10/17/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "Assemblizer.h"

Assemblizer::Assemblizer::Assemblizer() {
	
}

void Assemblizer::Assemblizer::addInstruction(AssemblerInstruction *instruction){
	_instructions.push_back(instruction);
}

void Assemblizer::Assemblizer::addVariableDeclaration(Variable *v) {
	_variables.push_back(v);
}
string Assemblizer::Assemblizer::createAssemblerHead(){
	string ret;
	ret += "section .text\n";
	ret += "global _start\n";
	ret += "\n";
	
	ret += "_start:\n";
	
	return ret;
}

string Assemblizer::Assemblizer::createAssemblerTail(){
	string ret;
	
	ret += "mov eax,1\n";
	ret += "int 0x80\n";
	
	ret +="\n";
	ret += "section .data\n";
	for(Variable *v : _variables) {
		ret += v->getName() + " " + v->getAssemblerTypeString() + " " + v->getInitialValue() + "\n";
	}
	
	return ret;
}

string Assemblizer::Assemblizer::getFinalAssemblerCode(){
	string ret = createAssemblerHead();
	
	for(AssemblerInstruction *s : _instructions) {
		ret += s->getAssemblerCode();
	}
	ret += createAssemblerTail();
	
	return ret;
}