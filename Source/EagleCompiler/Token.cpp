//
//  Token.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/28/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Token.h"

ostream& operator<<(ostream& o, TokenType t) {
	switch(t) {
	case TokenType::Identifier: {
		o <<  "Identifier";
	}break;
	case TokenType::WhiteSpace: {
		o <<  "Whitespace";
	}break;
	case TokenType::LiteralNumber: {
		o << "LiteralNumber";
	}break;
	case TokenType::LiteralString: {
		o << "LiteralString";
	}break;
	case TokenType::StatementEnd: {
		o << "StatementEnd";
	}break;
	case TokenType::Bracked_Round_Open: {
		o<< "Bracked_Round_Open";
	}break;
    case TokenType::Bracked_Round_Close: {
		o<< "Bracked_Round_Close";
	}break;
    case TokenType::Bracked_Curly_Open: {
		o<< "Bracked_Curly_Open";
	}break;
    case TokenType::Bracked_Curly_Close: {
		o<< "Bracked_Curly_Close";
	}break;
    case TokenType::Bracked_Square_Open: {
		o<< "Bracked_Square_Open";
	}break;
    case TokenType::Bracked_Square_Close: {
		o<< "Bracked_Square_Close";
	}break;
	case TokenType::Operator_Not: {
		o << "Operator_Not";
	}break;
	case TokenType::Operator_Assignment: {
		o << "Operator_Assignment";
	}break;
	case TokenType::Operator_Plus: {
		o << "Operator_Plus";
	}break;
	case TokenType::Operator_Minus: {
		o << "Operator_Minus";
	}break;
	case TokenType::Operator_Div: {
		o << "Operator_Div";
	}break;
	case TokenType::Operator_Multiply: {
		o << "Operator_Multiply";
	}break;
	case TokenType::Operator_Equals: {
		o << "Operator_Equals";
	}break;
	case TokenType::Operator_GreaterThan: {
		o << "Operator_GreaterThan";
	}break;
	case TokenType::Operator_SmallerThan: {
		o << "Operator_SmallerThan";
	}break;
	case TokenType::Operator_GreaterThanOrEqual: {
		o << "Operator_GreaterThanOrEqual";
	}break;
	case TokenType::Operator_SmallerThanOrEqual: {
		o << "Operator_SmallerThanOrEqual";
	}break;
	case TokenType::Keyword_Var: {
		o << "Keyword_Var";
	}break;
	case TokenType::Keyword_Condition: {
		o << "Keyword_Condition";
	}break;
	case TokenType::Keyword_Do: {
		o << "Keyword_Do";
	}break;
	case TokenType::Keyword_Break: {
		o << "Keyword_Break";
	}break;
	case TokenType::Keyword_Continue: {
		o << "Keyword_Continue";
	}break;
	default: {
		o << "None";
	}break;

	}
	return o;
}


