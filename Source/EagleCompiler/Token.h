//
//  Token.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/28/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__Token__
#define __EagleCompiler__Token__

#include <iostream>
#include <string.h>
#include <list>
#include <map>

using namespace std;


/**
 * Represents a type of a token
 */
enum TokenType {
    
    None,                   // unspecified Token
    
    Identifier,             // abc | abc12
    
    LiteralNumber,          // 123 | 0xFF
    LiteralString,          // "blub"
    
    StatementEnd,           // ;
    
    Operator_Not,           // !
    Operator_Assignment,    // =
    Operator_Plus,          // +
    Operator_Minus,         // -
    
    Operator_Equals,        // ==
    Operator_GreaterThan,   // >
    Operator_SmallerThan,   // <
    
    
    
    // ...
    
};

typedef map<string, TokenType> TokenMap;

const TokenMap::value_type x[] = {
    make_pair(";", TokenType::StatementEnd),
    
    // Operators
    make_pair("==", TokenType::Operator_Assignment),
    make_pair("+", TokenType::Operator_Plus),
    make_pair("-", TokenType::Operator_Minus),
    make_pair("=", TokenType::Operator_Equals),
    make_pair(">", TokenType::Operator_GreaterThan),
    make_pair("<", TokenType::Operator_SmallerThan),
};

/**
 * Represents a Token
 
 * This class is immutable
 */
class Token
{
private:
    TokenType _type;
    string _value;
    
    Token();
    
    void Init(TokenType type, string value){
        _type = type;
        _value = value;
    }
    
public:
    
    // Constructors
    Token(TokenType type) { Init(type, NULL); };
    Token(TokenType type, string value) { Init(type, value); };
    
    /**
     * Gets the Type of this token
     */
    TokenType getType(){ return _type; };
    
    /**
     * Gets the Value(Literal) of this token
     */
    string getValue(){ return _value; }
    
};


#endif /* defined(__EagleCompiler__Token__) */
