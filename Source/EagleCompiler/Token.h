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

using namespace std;

/**
 * Represents a type of a token
 */
enum TokenType {
    
    Identifier,
    
    LiteralNumber,
    LiteralString,
    
    StatementEnd,
    
    Operator_Assignment,
    Operator_Add,
    Operator_Sub,
    
    // ...
    
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


class TokenList
{
private:
    
public:
    void add(Token& t);
    
    Token* next();
    
    string toString();
};



#endif /* defined(__EagleCompiler__Token__) */
