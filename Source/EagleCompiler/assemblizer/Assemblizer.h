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
namespace Assemblizer {

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

}




#endif /* defined(__EagleCompiler__Assemblizer__) */
