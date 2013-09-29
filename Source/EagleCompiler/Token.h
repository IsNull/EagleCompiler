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
    
    // Brackets
    Bracked_Round_Open,     // (
    Bracked_Round_Close,    // )
    Bracked_Curly_Open,     // {
    Bracked_Curly_Close,    // }
    Bracked_Square_Open,    // [
    Bracked_Square_Close,   // ]
    
    // Operator
    Operator_Not,           // !
    Operator_Assignment,    // =
    Operator_Plus,          // +
    Operator_Minus,         // -
    Operator_Div,           // /
    Operator_Multiply,      // *
    Operator_Equals,        // ==
    Operator_GreaterThan,   // >
    Operator_SmallerThan,   // <
    

    // ...
    
};

const map<TokenType, string> TokenNames {
    {None, "None"},
    
    {Identifier, "Identifier"},
    
    {LiteralNumber, "LiteralNumber"},
    {LiteralString, "LiteralString"},
    
    {StatementEnd, "StatementEnd"},
    
    // Brackets
    {Bracked_Round_Open,"Bracked_Round_Open"},
    {Bracked_Round_Close, "Bracked_Round_Close"},
    {Bracked_Curly_Open, "Bracked_Curly_Open"},
    {Bracked_Curly_Close,"Bracked_Curly_Close"},
    {Bracked_Square_Open,"Bracked_Square_Open"},
    {Bracked_Square_Close,"Bracked_Square_Close"},
    
    // Operator
    {Operator_Not, "Operator_Not"},
    {Operator_Assignment,"Operator_Assignment"},
    {Operator_Plus,"Operator_Plus"},
    {Operator_Minus,"Operator_Minus"},
    {Operator_Div, "Operator_Div"},
    {Operator_Multiply,"Operator_Multiply"},
    {Operator_Equals,"Operator_Equals"},
    {Operator_GreaterThan, "Operator_GreaterThan"},
    {Operator_SmallerThan,"Operator_SmallerThan"}
};


typedef map<string, TokenType> TokenMap;

const TokenMap TokenMap_Default =
    {
        {";", TokenType::StatementEnd},
    
    // Operators
        {"==", TokenType::Operator_Assignment},
        {"+", TokenType::Operator_Plus},
        {"-", TokenType::Operator_Minus},
        {"=", TokenType::Operator_Equals},
        {">", TokenType::Operator_GreaterThan},
        {"<", TokenType::Operator_SmallerThan}
        
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
    TokenType getType() const { return _type; };
    
    /**
     * Gets the Value(Literal) of this token
     */
    string getValue() const { return _value; }
    
    string toString() const {
        return "[" + TokenNames.find(_type)->second + "," + _value + "]";
    }
    
};


#endif /* defined(__EagleCompiler__Token__) */
