//
//  CodeProcedure
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#ifndef __EagleCompiler__CodeProcedure__
#define __EagleCompiler__CodeProcedure__

#include <string>

#include "CodeIdentifier.h"

using namespace std;

namespace AST {
	class CodeProcedureDeclaration;

	class CodeProcedure : public CodeIdentifier {
	private:
		CodeProcedureDeclaration* decl;
	public:
		CodeProcedure(string name) : CodeIdentifier(name) { };
		
		void setDeclaration(CodeProcedureDeclaration* procDecl) { decl = procDecl; };
		CodeProcedureDeclaration *getDeclaration() { return decl; };
		
		string code();
        
        
        friend std::ostream& operator<< (std::ostream& stream, const CodeProcedure& node) {
            stream << "CodeProcedure";
            return stream;
        };
	};
}

#endif

