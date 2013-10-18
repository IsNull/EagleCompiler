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

//This will add the value of the two operands and safe the new value in eax
class Addition : AssemblerInstruction {
private:
	int _op1;
	int _op2;
public:
	Addition(int op1, int op2);
	string getAssemblerCode();
};

//TODO Add a lot of AssemlberInstruction classes


#endif /* defined(__EagleCompiler__AssemblerInstruction__) */
