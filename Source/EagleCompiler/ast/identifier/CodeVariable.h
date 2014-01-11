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
		CodeType _type;
		int _stackOffset;
	public:
		CodeVariable(string name, CodeType type) : 
			CodeIdentifier(name), _type(type)
			{ };
		
		CodeType getType() { return _type; };
		
		string code();
		
		int getStackPos() { return _stackOffset; };
		void setStackPos(int i) { _stackOffset = i; };
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeVariable& node) {
            stream << "CodeVariable";
            return stream;
        };
	};
}

#endif

