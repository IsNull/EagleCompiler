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
    WhiteSpace,             // Spaces | Tabs | Newlines
    
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
    Operator_GreaterThanOrEqual,   // >=
    Operator_SmallerThanOrEqual,   // <=

    // Keywords
    
    Keyword_Var,            // var
    Keyword_Condition,      // if
    Keyword_Do,             // do
    Keyword_Break,          // break
    Keyword_Continue,       // continue
    
    // ...
    
};

const map<TokenType, string> TokenNames {
    {None, "None"},
    
    {TokenType::Identifier, "Identifier"},
    {TokenType::WhiteSpace, "Whitespace"},
    
    {TokenType::LiteralNumber, "LiteralNumber"},
    {TokenType::LiteralString, "LiteralString"},
    
    {TokenType::StatementEnd, "StatementEnd"},
    
    // Brackets
    {TokenType::Bracked_Round_Open,"Bracked_Round_Open"},
    {TokenType::Bracked_Round_Close, "Bracked_Round_Close"},
    {TokenType::Bracked_Curly_Open, "Bracked_Curly_Open"},
    {TokenType::Bracked_Curly_Close,"Bracked_Curly_Close"},
    {TokenType::Bracked_Square_Open,"Bracked_Square_Open"},
    {TokenType::Bracked_Square_Close,"Bracked_Square_Close"},
    
    // Operators
    {TokenType::Operator_Not, "Operator_Not"},
    {TokenType::Operator_Assignment,"Operator_Assignment"},
    {TokenType::Operator_Plus,"Operator_Plus"},
    {TokenType::Operator_Minus,"Operator_Minus"},
    {TokenType::Operator_Div, "Operator_Div"},
    {TokenType::Operator_Multiply,"Operator_Multiply"},
    {TokenType::Operator_Equals,"Operator_Equals"},
    {TokenType::Operator_GreaterThan, "Operator_GreaterThan"},
    {TokenType::Operator_SmallerThan,"Operator_SmallerThan"},
    {TokenType::Operator_GreaterThanOrEqual, "Operator_GreaterThanOrEqual"},
    {TokenType::Operator_SmallerThanOrEqual,"Operator_SmallerThanOrEqual"},
    
    // Keywords
    {TokenType::Keyword_Var, "Keyword_Var"},
    {TokenType::Keyword_Condition,"Keyword_Condition"},
    {TokenType::Keyword_Do,"Keyword_Do"},
    {TokenType::Keyword_Break, "Keyword_Break"},
    {TokenType::Keyword_Continue,"Keyword_Continue"}
};

// Represents a mapping of string to a token type
typedef map<string, TokenType> TokenMap;

// Tokenmap for the default context
// (for comments or literal strings, there are diffrent contexts)
const TokenMap TokenMap_Default =
    {
        {";", TokenType::StatementEnd},
    
    // Operators
        {"==", TokenType::Operator_Equals},
        {"+", TokenType::Operator_Plus},
        {"-", TokenType::Operator_Minus},
        {"=", TokenType::Operator_Assignment},
        {">", TokenType::Operator_GreaterThan},
        {"<", TokenType::Operator_SmallerThan},
        {">=", TokenType::Operator_GreaterThanOrEqual},
        {"<=", TokenType::Operator_SmallerThanOrEqual},
        {"*", TokenType::Operator_Multiply},
        {"/", TokenType::Operator_Div},
        {"!", TokenType::Operator_Not},
        
    // Brackets
        {"(", TokenType::Bracked_Round_Open},
        {")", TokenType::Bracked_Round_Close},
        {"{", TokenType::Bracked_Curly_Open},
        {"}", TokenType::Bracked_Curly_Close},
        {"[", TokenType::Bracked_Square_Open},
        {"]", TokenType::Bracked_Square_Close}
        
    };
/*
Keyword_Var,            // var
Keyword_Condition,      // if
Keyword_Do,             // do
Keyword_Break,          // break
Keyword_Continue,       // continue
*/
const TokenMap KeywordTokens =
{
    {"var", TokenType::Keyword_Var},
    {"if", TokenType::Keyword_Condition},
    {"do", TokenType::Keyword_Do},
    {"break", TokenType::Keyword_Break},
    {"continue", TokenType::Keyword_Continue}
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
    
    
    
    friend std::ostream& operator<< (std::ostream& stream, const Token& token) {
        stream << "[" + TokenNames.find(token._type)->second + "," + token._value + "]";
        return stream;
    }
    
    /**
     * Find the keyword for the given keyword
     * If the given string is not a keyword TokenType::None is returned.
     *
     */
    static TokenType findKeyword(string possibleKeyword){
        TokenMap::const_iterator it = KeywordTokens.find(possibleKeyword);
        return (it == KeywordTokens.end()) ? TokenType::None : it->second;
    }
    
};


#endif /* defined(__EagleCompiler__Token__) */
