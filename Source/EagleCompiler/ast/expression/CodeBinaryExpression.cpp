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

using namespace std;
using namespace AST;


string AST::CodeBinaryExpression::code() {
	string ret;
	
	ret += _left->code();
	ret += "push eax\n";
	
	if(_binaryOperator == BINARYOPERATOR::COND_AND) {
		
	} else if(_binaryOperator == BINARYOPERATOR::COND_OR) {
		
	} else {
		
		ret += _right->code();
		
		ret += "pop ebx\n";
		
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
				ret += "setle eax\n";
			break;
			case BINARYOPERATOR::GREATER_EQ :
				ret += "cmp eax,ebx\n";
				ret += "setl eax\n";
			break;
			case BINARYOPERATOR::EQUAL:
				ret += "cmp eax,ebx\n";
				ret += "sete eax\n";
			break;
			case BINARYOPERATOR::NOT_EQ :
				ret += "cmp eax,ebx\n";
				ret += "setne eax\n";
			break;
			case BINARYOPERATOR::GREATER :
				ret += "cmp eax,ebx\n";
				ret += "setg eax\n";
			break;
			case BINARYOPERATOR::LESS_EQ :
				ret += "cmp eax,ebx\n";
				ret += "setle eax\n";
			break;
			case BINARYOPERATOR::STR_CONCAT :
				
			break;
			default: break;
		}
	}
	
	return _left->code() + AST::BinaryOperatorString.find(_binaryOperator)->second + _right->code();
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
