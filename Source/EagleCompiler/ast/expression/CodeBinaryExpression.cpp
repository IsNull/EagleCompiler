//
//  CodeBinaryExpression.cpp
//  EagleCompiler
//
//  Created by Samuel Stachelski on 2013-12-30.
//  Copyright (c) 2013 Samuel Stachelski. All rights reserved.
//

#include <string.h>
#include <map>

#include "CodeBinaryExpression.h"
#include "../CodeProgram.h"

using namespace std;
using namespace AST;


string AST::CodeBinaryExpression::code() {
	string ret;
	
	ret += _left->code();
	
	if(_binaryOperator == BINARYOPERATOR::COND_AND) {
		ret += to_string((long) this) + "cond_and:\n";
		ret += "cmp eax,0\n";
		ret += "je .condjump\n";
		ret += "push eax\n";
		ret += _right->code();
		ret += "mov ebx,eax\n";
		ret += "pop eax\n";
		ret += "imul eax,ebx\n";
		ret += ".condjump:\n";
	} else if(_binaryOperator == BINARYOPERATOR::COND_OR) {
		ret += to_string((long) this) + "cond_or:\n";
		ret += "cmp eax,0\n";
		ret += "jne .condjump\n";
		ret += "push eax\n";
		ret += _right->code();
		ret += "mov ebx,eax\n";
		ret += "pop eax\n";
		ret += "add eax,ebx\n";
		ret += ".condjump:\n";
	} else {
		
		ret += "push eax\n";
		ret += _right->code();
		ret += "mov ebx,eax\n";
		ret += "pop eax\n";
		
		switch(_binaryOperator) {
			case BINARYOPERATOR::TIMES :
				ret += "imul ebx\n";
			break;
			case BINARYOPERATOR::DIV :
				ret += "idiv ebx\n";
			break;
			case BINARYOPERATOR::MOD :
				ret += "idiv ebx\n";
				ret += "mov eax,edx";
			break;
			case BINARYOPERATOR::PLUS :
				ret += "add eax,ebx\n";
			break;
			case BINARYOPERATOR::MINUS :
				ret += "sub eax,ebx\n";
			break;
			case BINARYOPERATOR::LESS :
				ret += "cmp eax,ebx\n";
				ret += "setl al\n";
				ret += "and eax,0xFF\n";
			break;
			case BINARYOPERATOR::GREATER_EQ :
				ret += "cmp eax,ebx\n";
				ret += "setge al\n";
				ret += "and eax,0xFF\n";
			break;
			case BINARYOPERATOR::EQUAL:
				ret += "cmp eax,ebx\n";
				ret += "sete al\n";
				ret += "and eax,0xFF\n";
			break;
			case BINARYOPERATOR::NOT_EQ :
				ret += "cmp eax,ebx\n";
				ret += "setne al\n";
				ret += "and eax,0xFF\n";
			break;
			case BINARYOPERATOR::GREATER :
				ret += "cmp eax,ebx\n";
				ret += "setg al\n";
				ret += "and eax,0xFF\n";
			break;
			case BINARYOPERATOR::LESS_EQ :
				ret += "cmp eax,ebx\n";
				ret += "setle al\n";
				ret += "and eax,0xFF\n";
			break;
			case BINARYOPERATOR::STR_CONCAT :
			{
				//left is in eax
				if(_left->getType() == CodeType::BOOL) {
					ret += to_string((long)this) + "_booltostring_left: ";
					ret += "mov ecx,booltostringfalse\n";
					ret += "cmp eax,0\n";
					ret += "je .booljmp\n";
					ret += "mov ecx,booltostringtrue\n";
					ret += ".booljmp: mov eax,ecx\n";
				}
				//right is in ebx
				if(_right->getType() == CodeType::BOOL) {
					ret += to_string((long)this) + "_booltostring_right: ";
					ret += "mov ecx,booltostringfalse\n";
					ret += "cmp ebx,0\n";
					ret += "je .booljmp\n";
					ret += "mov ecx,booltostringtrue\n";
					ret += ".booljmp: mov ebx,ecx\n";
				}
				
				//choose format string
				string formatString("concat_string_string");
				if(_left->getType() == CodeType::STRING || _left->getType() == CodeType::BOOL)  {
					if(_right->getType() == CodeType::INT32) {
						formatString = "concat_string_number";
					}
				} else if(_left->getType() == CodeType::INT32) {
					if(_right->getType() == CodeType::STRING || _right->getType() == CodeType::BOOL)  {
						formatString = "concat_number_string";
					} else if (_right->getType() == CodeType::INT32) {
						formatString = "concat_number_number";
					}
				}

				ret += "push ebx\n";
				ret += "push eax\n";
				ret += "push dword " + formatString + "\n";
				ret += "push dword " + to_string(STRING::BUFFER_LEN-1) + "\n";
				ret += "push dword " + CodeProgram::tmp1->label() + "\n";
				ret += "call " + CodeProgram::SNPRINTF + "\n";
				ret += "add esp,15\n";
				
				//copy the string to tmp2, for sub-expressions
				ret += "push dword " + to_string(STRING::BUFFER_LEN-1) + "\n";
				ret += "push dword " + CodeProgram::tmp1->label() + "\n";
				ret += "push dword " + CodeProgram::tmp2->label() + "\n";
				ret += "call " + CodeProgram::STRNCPY + "\n";
				ret += "add esp,12\n";
				
				ret += "mov eax," + CodeProgram::tmp2->label() + "\n";
			} break;
			default: break;
		}
	}
	
	return ret;
};

CodeType CodeBinaryExpression::getType(){
    CodeType type = CodeType::UNKNOWN;
    
    switch (_binaryOperator) {
            
        case BINARYOPERATOR::TIMES:
        case BINARYOPERATOR::DIV:
        case BINARYOPERATOR::MOD:
        case BINARYOPERATOR::PLUS:
        case BINARYOPERATOR::MINUS:
            type = CodeType::INT32;
            break;
            
        case BINARYOPERATOR::LESS:
        case BINARYOPERATOR::GREATER_EQ:
        case BINARYOPERATOR::EQUAL:
        case BINARYOPERATOR::NOT_EQ:
        case BINARYOPERATOR::GREATER:
        case BINARYOPERATOR::LESS_EQ:
        case BINARYOPERATOR::COND_AND:
        case BINARYOPERATOR::COND_OR:
            type = CodeType::BOOL;
            break;
        case BINARYOPERATOR::STR_CONCAT:
            type = CodeType::STRING;
            break;
            
        default:
            cout << "ERROR: getType: unhandled operator: " << BinaryOperatorString.find(_binaryOperator)->second << "\n";
            break;
    }
    
    return type;
};
