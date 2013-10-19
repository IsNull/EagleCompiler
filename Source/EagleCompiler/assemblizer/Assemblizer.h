//
//  Assemblizer.h
//  EagleCompiler
//
//  Created by Samuel Stachelski on 10/17/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//
#ifndef __EagleCompiler__Assemblizer__
#define __EagleCompiler__Assemblizer__

#include <list>
#include "AssemblerInstruction.h"

using namespace std;

//Variable Classes, just for assemblizer
class Variable{
private:
	string _name;
public:
	Variable(string name);
	string getName();
	
	virtual string getAssemblerTypeString() = 0;
	virtual string getInitialValue() = 0;
};

class NumericVariable : public Variable{
private:
	int32_t _init;
public:
	NumericVariable(string name, int32_t init);
	string getAssemblerTypeString();
	string getInitialValue();
};

class StringVariable: public Variable{
private:
	string _init;
public:
	StringVariable(string name, string init);
	string getAssemblerTypeString();
	string getInitialValue();
};

class Assemblizer {
private:

	list<AssemblerInstruction *> _instructions; // List of all instructions
    list<Variable *> _variables; // List of al variables
    
    string createAssemblerHead();
	string createAssemblerTail();

public:
	Assemblizer();
	
	void addInstruction(AssemblerInstruction *instruction);
	
	void addVariableDeclaration(Variable *v);

	
	string getFinalAssemblerCode();
};




#endif /* defined(__EagleCompiler__Assemblizer__) */
