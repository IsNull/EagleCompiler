//
//  CodeVariable
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeVariable__
#define __EagleCompiler__CodeVariable__

#include <string>
#include <map>

#include "CodeIdentifier.h"
#include "../type/CodeType.h"
#include "../expression/CodeExpressionVariable.h"
#include "../expression/CodeExpressionInitializeVariable.h"

using namespace std;

namespace AST {
		
	enum class FLOWMODE {
		EMPTY,
		IN,
		OUT,
		INOUT
	};
	
	enum class MECHMODE {
		EMPTY,
		COPY,
		REF
	};

	enum class CHANGEMODE {
		EMPTY,
		CONST,
		VAR
	};
	
	extern map<FLOWMODE, string> FlowModeString;
	extern map<MECHMODE, string> MechModeString;
	extern map<CHANGEMODE, string> ChangeModeString;

	class CodeVariable : public CodeIdentifier {
	private:
		CodeType *_type;
		CodeExpressionVariable *_expression;
		CodeExpressionInitializeVariable *_initExpression;
	public:
		CodeVariable(string name, CodeType *type) : 
			CodeIdentifier(name), _type(type), 
			_expression( new CodeExpressionVariable(this)),
			_initExpression(new CodeExpressionInitializeVariable(this)) { };
		
		CodeType *getType() { return _type; };
		CodeExpressionVariable *asExpression() { return _expression; };
		CodeExpressionInitializeVariable *asInitExpression() { return _initExpression; };
		
		string code();
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeVariable& node) {
            stream << "CodeVariable";
            return stream;
        };
	};
}

#endif

