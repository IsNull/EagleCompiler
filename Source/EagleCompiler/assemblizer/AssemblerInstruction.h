//
//  AssemblerInstruction.h
//  EagleCompiler
//
//  Created by Samuel Stachelski on 10/17/13.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__AssemblerInstruction__
#define __EagleCompiler__AssemblerInstruction__

#include <string>

using namespace std;

//Interface definition for assembler instructions
class AssemblerInstruction {
public:	
	virtual string getAssemblerCode() = 0; // Returns the string, which will finaly be written to the output
};

//This will add the value of the two variables and safe the new value in eax
class AdditionInstruction : public AssemblerInstruction {
private:
	string _op1;
	string _op2;
public:
	AdditionInstruction(string op1, string op2);
	string getAssemblerCode();
};

class WriteToStandardOutputInstruction : public AssemblerInstruction {
private:
	string _op1;
public:
	WriteToStandardOutputInstruction(string op1);
	string getAssemblerCode();
};

//TODO Add a lot of AssemlberInstruction classes


#endif /* defined(__EagleCompiler__AssemblerInstruction__) */
