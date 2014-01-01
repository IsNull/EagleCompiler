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

#include "CodeIdentifier.h"
#include "../type/CodeType.h"

using namespace std;

namespace AST {
	
	enum class FLOWMODE {
		EMPTY,
	};
	enum class MECHMODE {
		EMPTY,
	};
	enum class CHANGEMODE {
		EMPTY,
	};
	
	class CodeVariable : public CodeIdentifier {
	private:
		CodeType *_type;
	public:
		CodeVariable(string name, CodeType *type) : CodeIdentifier(name), _type(type) { };
		
		CodeType *getType() { return _type; };
		
		string code();
	};
}

#endif

