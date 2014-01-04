//
//  CodeParameter
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeParameter__
#define __EagleCompiler__CodeParameter__

#include <string>

#include "CodeObject.h"
#include "identifier/CodeVariable.h"

using namespace std;

namespace AST {
	
	class CodeParameter : public CodeObject {
	private:
		FLOWMODE _flowmode;
		MECHMODE _mechmode;
		CHANGEMODE _changemode;
		CodeVariable *_variable;
	public:
		CodeParameter(FLOWMODE flowmode, MECHMODE mechmode, CHANGEMODE changemode, CodeVariable *variable) :
			_flowmode(flowmode), _mechmode(mechmode), _changemode(changemode), _variable(variable) { };
			
		FLOWMODE getFlowMode() { return _flowmode; };
		MECHMODE getMechMode() { return _mechmode; };
		CHANGEMODE getChangeMode() { return _changemode; };
		CodeVariable *getVariable() { return _variable; };
		
		string code();
        
        virtual string toString()const{ return "<CodeParameter>";}
	};
    

}

#endif

