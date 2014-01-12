//
//  CodeProgram.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>

#include "CodeProgram.h"

#include "declaration/CodeStorageDeclaration.h"
#include "declaration/CodeProcedureDeclaration.h"
#include "expression/CodeExpressionLiteral.h"

using namespace std;

string AST::CodeProgram::code() {
	
	//Prepare variables
	for (int i=0; i<_globalDecl.size(); i++) {
		CodeStorageDeclaration * decl = dynamic_cast<CodeStorageDeclaration*>(_globalDecl[i]);
		if(decl != nullptr) {
			decl->getVariable()->setStackPos(-i*4);
		}
	}
	string ret = "global main\n\n";
	ret += "extern  printf\n";
	ret += "extern  strncpy\n";
		
	ret += "\n";
	
	ret += "section .data\n";
	ret += "int32print: db \"%d\",10,0\n";
	ret += "stringprint: db \"%s\",10,0\n";
	for(auto e : CodeExpressionLiteral::getAllLiterals()) {
		if(e->getVariable()->getType() == CodeType::STRING) {
			ret += e->getVariable()->label() + ": dw \"" + e->getValue() + "\",0\n";
		}
	}
	
	ret += "\n";
	ret += "section .bss\n";
	for (int i=0; i<_globalDecl.size(); i++) {
		CodeStorageDeclaration *decl = dynamic_cast<CodeStorageDeclaration*>(_globalDecl[i]);
		if(decl != nullptr) {
			if(decl->getVariable()->getType() == CodeType::STRING) {
				ret += decl->getVariable()->label() + ": resb 255\n";
			}
		} else {
			CodeInvokableDeclaration *decl = dynamic_cast<CodeInvokableDeclaration*>(_globalDecl[i]);
			for(auto e : decl->getLocalStorageDeclarations()) {
				if(e->getVariable()->getType() == CodeType::STRING) {
					ret += e->getVariable()->label() + ": resb 255\n";
				}
			}
		}
	}
	ret += "\n";
	
	ret += "section .text\n";
	ret += "main:\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string(_globalDecl.size()*4) + "\n";

	for (auto p : _progStatements) {
		ret += p->code();
	}
	ret += "leave\n";
	ret += "ret\n";
	
	for (int i=0; i<_globalDecl.size(); i++) {
		CodeInvokableDeclaration *decl = dynamic_cast<CodeInvokableDeclaration*>(_globalDecl[i]);
		if(decl != nullptr) {
			ret += "\n" + decl->code();
		}
	}
	
	return ret;
}

