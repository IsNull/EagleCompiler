//
//  Assemblizer.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 10/17/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include "Assemblizer.h"

Assemblizer::Assemblizer() {
	
}

void Assemblizer::addInstruction(AssemblerInstruction *instruction){
	_instructions.push_back(instruction);
}

void Assemblizer::addVariableDeclaration(Variable *v) {
	_variables.push_back(v);
}
string Assemblizer::createAssemblerHead(){
	string ret;
	ret += ".global _start\n";
	
	ret += ".data\n";
	
	for(Variable *v : _variables) {
		ret += v->getName() + ": " + v->getAssemblerTypeString() + " " + v->getInitialValue() + "\n";
	}
	ret += "\n";
	
	ret += ".text\n";
	ret += "_start:\n";
	
	return ret;
}

string Assemblizer::createAssemblerTail(){
	string ret;
	
	ret += "movl $0, %eax\n";
	ret += "movl $1,%eax\n";
	ret += "int $0x80\n";
	
	return ret;
}

string Assemblizer::getFinalAssemblerCode(){
	string ret = createAssemblerHead();
	
	for(AssemblerInstruction *s : _instructions) {
		ret += s->getAssemblerCode();
	}
	ret += createAssemblerTail();
	
	return ret;
}