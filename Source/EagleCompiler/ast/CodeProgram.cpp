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
#include "declaration/CodeFunctionDeclaration.h"
#include "expression/CodeExpressionLiteral.h"
#include "identifier/CodeVariable.h"
// 
using namespace std;

AST::CodeVariable *AST::CodeProgram::tmp1 = new AST::CodeVariable("__tmp1__", AST::CodeType::STRING);
AST::CodeVariable *AST::CodeProgram::tmp2 = new AST::CodeVariable("__tmp2__", AST::CodeType::STRING);
	
string AST::CodeProgram::code() {
	
	int c=1;
	//Prepare variables
	for (int i=0; i<_globalDecl.size(); i++) {
		CodeStorageDeclaration * decl = dynamic_cast<CodeStorageDeclaration*>(_globalDecl[i]);
		if(decl != nullptr) {
			if(decl->getVariable()->getType() != CodeType::STRING)
			decl->getVariable()->setStackPos(-(c++)*4);
		}
	}
	string ret = "global main\n\n";
	ret += "extern  printf\n";
	ret += "extern  scanf\n";
	ret += "extern  strncpy\n";
	ret += "extern  snprintf\n";

	ret += "\n";
	
	ret += "section .data\n";
	ret += "int32print: db \"%d\",10,0\n";
	ret += "stringprint: db \"%s\",10,0\n";
	ret += "int32scan: db \"%d\",0\n";
	ret += "stringscan: db \"%s\",0\n";
	ret += "booltostringtrue: db \"true\",0\n";
	ret += "booltostringfalse: db \"false\",0\n";
	ret += "terminalinput: db \">\",0\n";
	
	ret += "concat_string_string: db \"%s%s\",0\n";
	ret += "concat_string_number: db \"%s%d\",0\n";
	ret += "concat_number_string: db \"%d%s\",0\n";
	ret += "concat_number_number: db \"%d%d\",0\n";
	
	for(auto e : CodeExpressionLiteral::getAllLiterals()) {
		if(e->getVariable()->getType() == CodeType::STRING) {
			ret += e->getVariable()->label() + ": dw \"" + e->getValue() + "\",0\n";
		}
	}
	
	ret += "\n";
	ret += "section .bss\n";
	ret += tmp1->label() + ": resb " + to_string(STRING::BUFFER_LEN) + "\n";
	ret += tmp2->label() + ": resb " + to_string(STRING::BUFFER_LEN) + "\n";
	int globalStoDecl = 0;
	for (int i=0; i<_globalDecl.size(); i++) {
		CodeStorageDeclaration *decl = dynamic_cast<CodeStorageDeclaration*>(_globalDecl[i]);
		//Add globalDecl Strings
		if(decl != nullptr) {
			if(decl->getVariable()->getType() == CodeType::STRING) {
				ret += decl->getVariable()->label() + ": resb 255\n";
			} else {
				globalStoDecl++;
			}
		} else {
			//Add Invokable string
			CodeInvokableDeclaration *decl = dynamic_cast<CodeInvokableDeclaration*>(_globalDecl[i]);
			for(auto e : decl->getLocalStorageDeclarations()) {
				if(e->getVariable()->getType() == CodeType::STRING) {
					ret += e->getVariable()->label() + ": resb 255\n";
				}
			}
			for(auto e : decl->getParameters()) {
				if(e->getVariable()->getType() == CodeType::STRING) {
					ret += e->getVariable()->label() + ": resb 255\n";
				}
			}
			CodeFunctionDeclaration *fundecl = dynamic_cast<CodeFunctionDeclaration*>(decl);
			if(fundecl != nullptr) {
				if (fundecl->getReturnDeclaration()->getVariable()->getType() == CodeType::STRING) {
					ret += fundecl->getReturnDeclaration()->getVariable()->label() + ": resb 255\n";
				}
			}
				
		}
	}
	ret += "\n";
	
	ret += "section .text\n";
	ret += "main:\n";
	
	ret += "push ebp\n";
	ret += "mov ebp,esp\n";
	ret += "sub esp," + to_string(globalStoDecl*4) + "\n";
	

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

