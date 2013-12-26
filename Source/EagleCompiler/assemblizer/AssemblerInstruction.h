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
namespace Assemblizer {
	
	extern int tmpVariableCounter;

	//Interface definition for assembler instructions
	class AssemblerInstruction {
	public:	
		virtual string getAssemblerCode() = 0; // Returns the string, which will finaly be written to the output
	};
	
	class ArithmeticInstruction : public AssemblerInstruction {
	public:
		string ADD = "add";
		string SUBTRACT = "sub";
		string MULTIPLY = "imul";
		string DIVIDE = "idiv";
		string MODULO = "idiv";
		
		ArithmeticInstruction(string param1, string param2, string op);
		string getAssemblerCode();
	private:
		string _param1;
		string _param2;
		string _operator;
	};
	
	class Comparison : public AssemblerInstruction {
	public:
		string GREATER = "g";
		string LESS = "l";
		string EQUAL = "e";
		string GREATER_OR_EQUAL = "ge";
		string LESS_OR_EQUAL = "le";
		string NOT_EQUAL = "ne";
		
		Comparison(string param1, string param2, string op);
		string getAssemblerCode();
	private:
		string _param1;
		string _param2;
		string _operator;
	};
	
	class BooleanCondition : public AssemblerInstruction {
	public:
		string AND = "and";
		string OR = "or";
		
		BooleanCondition(string param1, string param2, string op);
		string getAssemblerCode();
	private:
		string _param1;
		string _param2;
		string _operator;
	};

	class WriteToStandardOutputInstruction : public AssemblerInstruction {
	private:
		string _op1;
	public:
		WriteToStandardOutputInstruction(string op1);
		string getAssemblerCode();
	};

}

//TODO Add a lot of AssemlberInstruction classes


#endif /* defined(__EagleCompiler__AssemblerInstruction__) */
