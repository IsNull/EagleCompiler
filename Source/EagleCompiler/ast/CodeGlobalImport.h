//
//  CodeGlobalImport
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeGlobalImport__
#define __EagleCompiler__CodeGlobalImport__

#include <string>

#include "CodeObject.h"
#include "CodeParameter.h"
#include "identifier/CodeVariable.h"

using namespace std;

namespace AST {
	class CodeGlobalImport : public CodeObject {
	private:
		CodeParameter importParameter;
	public:
		CodeGlobalImport(FLOWMODE flowmode, CHANGEMODE changemode, CodeVariable *variable) :
			importParameter(flowmode, MECHMODE::EMPTY, changemode, variable) { };
			
		FLOWMODE getFlowMode() { return importParameter.getFlowMode(); };
		CHANGEMODE getChangeMode() { return importParameter.getChangeMode(); };
		CodeVariable* getVariable() { return importParameter.getVariable(); };
		
		string code();
        
        virtual string toString() const { return "<CodeGlobalImport>";}
	};
}

#endif

