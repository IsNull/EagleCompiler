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
    Sentinel,               // Marks end of Token stream
    WhiteSpace,             // Spaces | Tabs
    NewLine,                // Newlines
    
    Identifier,             // abc | abc12
    
    LiteralNumber,          // 123 | 0xFF
    LiteralString,          // normal text
    LiteralStringToggle,    // "
    StringInlineExprToggle, // %
    
    StatementEnd,           // ;
    
    // Comments
    
    Comment_ML_Start,       // /*
    Comment_ML_End,         // */
    Comment_Line,           // //
    
    // Brackets
    Bracked_Round_Open,     // (
    Bracked_Round_Close,    // )
    Bracked_Curly_Open,     // {
    Bracked_Curly_Close,    // }
    Bracked_Square_Open,    // [
    Bracked_Square_Close,   // ]
    
    // Operator
    Operator_Not,           // !
    Operator_Assignment,    // :=
    Operator_Plus,          // +
    Operator_Minus,         // -
    Operator_Div,           // div
    Operator_Multiply,      // *
    Operator_Modulo,        // mod
    Operator_Equals,        // =
    Operator_GreaterThan,   // >
    Operator_SmallerThan,   // <
    Operator_GreaterThanOrEqual,   // >=
    Operator_SmallerThanOrEqual,   // <=
    Operator_StringConcat,  // &
    
    Operator_BOOL_AND,      // &&
    Operator_BOOL_OR,       // ||
    Operator_BOOL_CAND,     // |&
    Operator_BOOL_COR,      // |?
    
    Semicolon,  // ;
    Colon,      // :
    Comma,      // ,
    
    // Keywords
    
    Keyword_Init,           // init
    Keyword_Program,        // program
    Keyword_ProgramEnd,     // endprogram
    
    Keyword_Call,
    Keyword_Const,
    Keyword_Global,
    Keyword_Local,
    Keyword_Copy,
    Keyword_Ref,
    Keyword_In,
    Keyword_Out,
    Keyword_InOut,
    
    Keyword_Var,            // var
    
    Keyword_Proc,           // proc
    Keyword_ProcEnd,        // endproc
    
    Keyword_While,          // while
    Keyword_WhileEnd,       // endwhile
    Keyword_Condition,      // if
    Keyword_Then,           // then
    Keyword_ConditionEnd,   // endif
    Keyword_Do,             // do
    Keyword_Break,          // break
    Keyword_Continue,       // continue
    Keyword_Return,         // returns
    
    // ...
    Keyword_True,
    Keyword_False,
    
    Type_Int,
    Type_Bool,
    Type_String,
    
    // Metadata Groups
    
    Group_Literal,
    Group_Type,
    Group_Flowmode,
    Group_Mechmode,
    Group_Changemode,
    Group_AddOpr,
    Group_MultOpr,
    Group_RelOpr,
    Group_BoolOpr
};

typedef map<TokenType, list<TokenType>> TokenGroupMap;

/**
 * Since the parse table handles certain token as a group,
 * we define them here as well to handle them adequatly
 *
 */
const TokenGroupMap TokenGroups {
    
    {TokenType::Group_Literal,
        { TokenType::Keyword_True, TokenType::Keyword_False } },
    {TokenType::Group_Type,
        { TokenType::Type_Int, TokenType::Type_Bool, TokenType::Type_String } },
    {TokenType::Group_Flowmode,
        { TokenType::Keyword_In, TokenType::Keyword_Out, TokenType::Keyword_InOut} },
    {TokenType::Group_Mechmode,
        { TokenType::Keyword_Copy, TokenType::Keyword_Ref } },
    {TokenType::Group_Changemode,
        { TokenType::Keyword_Var, TokenType::Keyword_Const } },
    {TokenType::Group_AddOpr,
        { TokenType::Operator_Plus, TokenType::Operator_Minus } },
    {TokenType::Group_MultOpr,
        { TokenType::Operator_Multiply, TokenType::Operator_Div } },
    {TokenType::Group_RelOpr,
        {TokenType::Operator_Equals, TokenType::Operator_GreaterThan,TokenType::Operator_SmallerThan,TokenType::Operator_GreaterThanOrEqual,TokenType::Operator_SmallerThanOrEqual} },
    {TokenType::Group_BoolOpr,
        { TokenType::Operator_BOOL_AND, TokenType::Operator_BOOL_OR, TokenType::Operator_BOOL_CAND, TokenType::Operator_BOOL_COR } }
};



const map<TokenType, const string> TokenNames {
        {None, "None"},
        {TokenType::Sentinel, "Sentinel"},
    
        {TokenType::Identifier, "Identifier"},
        {TokenType::WhiteSpace, "Whitespace"},
        {TokenType::NewLine, "NewLine"},
    
        {TokenType::LiteralNumber, "LiteralNumber"},
        {TokenType::LiteralString, "LiteralString"},
    
        {TokenType::StatementEnd, "StatementEnd"},
    
        // Comments
        {TokenType::Comment_ML_Start,"Comment_ML_Start"},
        {TokenType::Comment_ML_End, "Comment_ML_End"},
        {TokenType::Comment_Line, "Comment_Line"},
    
        // Brackets
        {TokenType::Bracked_Round_Open,"LPAREN"},
        {TokenType::Bracked_Round_Close, "RPAREN"},
        {TokenType::Bracked_Curly_Open, "Bracked_Curly_Open"},
        {TokenType::Bracked_Curly_Close,"Bracked_Curly_Close"},
        {TokenType::Bracked_Square_Open,"Bracked_Square_Open"},
        {TokenType::Bracked_Square_Close,"Bracked_Square_Close"},
    
        // Operators
        {TokenType::Operator_Not, "NOT"},
        {TokenType::Operator_Assignment,"BECOMES"},
    
        {TokenType::Group_AddOpr,"ADDOPR"},
        {TokenType::Operator_Plus,"ADDOPR_PLUS"},
        {TokenType::Operator_Minus,"ADDOPR_MINUS"},
    
    
        {TokenType::Group_MultOpr, "MULTOPR"},
        {TokenType::Operator_Div, "MULTOPR_DIV"},
        {TokenType::Operator_Multiply,"MULTOPR_TIMES"},
        {TokenType::Operator_Modulo,"MULTOPR_MOD"},
    
        {TokenType::Group_RelOpr,"RELOPR"},
        {TokenType::Operator_Equals,"RELOPR_EQ"},
        {TokenType::Operator_GreaterThan, "RELOPR_GT"},
        {TokenType::Operator_SmallerThan,"RELOPR_ST"},
        {TokenType::Operator_GreaterThanOrEqual, "RELOPR_GE"},
        {TokenType::Operator_SmallerThanOrEqual,"RELOPR_SE"},
    
        {TokenType::Group_BoolOpr, "BOOLOPR"},
        {TokenType::Operator_BOOL_AND, "BOOLOPR_AND"},
        {TokenType::Operator_BOOL_OR,"BOOLOPR_OR"},
        {TokenType::Operator_BOOL_CAND, "BOOLOPR_CAND"},
        {TokenType::Operator_BOOL_COR,"BOOLOPR_COR"},
    
    
        // Keywords
        {TokenType::Colon, "COLON"},
        {TokenType::Semicolon, "SEMICOLON"},
        {TokenType::Comma, "Comma"},
    
        // modifiers
        {TokenType::Keyword_Init, "INIT"},
        {TokenType::Keyword_Call, "CALL"},
        {TokenType::Keyword_Global,"GLOBAL"},
        {TokenType::Keyword_Local,"LOCAL"},
    
        {TokenType::Group_Changemode, "CHANGEMODE"},
        {TokenType::Keyword_Var, "CHANGEMODE_VAR"},
        {TokenType::Keyword_Const,"CHANGEMODE_CONST"},
    
        {TokenType::Group_Mechmode, "MECHMODE"},
        {TokenType::Keyword_Copy, "MECHMODE_COPY"},
        {TokenType::Keyword_Ref,"MECHMODE_REF"},
    
        {TokenType::Group_Flowmode,"FLOWMODE"},
        {TokenType::Keyword_In,"FLOWMODE_IN"},
        {TokenType::Keyword_Out, "FLOWMODE_OUT"},
        {TokenType::Keyword_InOut,"FLOWMODE_INOUT"},
    
        // flow
        {TokenType::Keyword_Proc, "PROC"},
        {TokenType::Keyword_ProcEnd, "ENDPROC"},
        {TokenType::Keyword_While, "WHILE"},
        {TokenType::Keyword_WhileEnd, "ENDWHILE"},
        {TokenType::Keyword_Program, "PROGRAM"},
        {TokenType::Keyword_ProgramEnd, "ENDPROGRAM"},
    
        {TokenType::Keyword_Condition,"IF"}, // if
        {TokenType::Keyword_Then,"THEN"}, // then
        {TokenType::Keyword_ConditionEnd,"ENDIF"}, // endif
        {TokenType::Keyword_Do,"DO"},
        {TokenType::Keyword_Break, "BREAK"},
        {TokenType::Keyword_Continue,"SKIP"},
        {TokenType::Keyword_Return,"RETURNS"},
    
        {TokenType::Group_Type, "TYPE"},
        {TokenType::Type_Int, "TYPE_Int32"},
        {TokenType::Type_Bool,"TYPE_BOOL"},
        {TokenType::Type_String,"TYPE_STRING"},
    
    
        {TokenType::Group_Literal, "LITERAL"},
        {TokenType::Keyword_True, "LITERAL_TRUE"},
        {TokenType::Keyword_False,"LITERAL_FALSE"}
    };


ostream& operator<<(ostream& o, TokenType t);

// Represents a mapping of string to a token type
typedef map<string, TokenType> TokenMap;


/*
*
*/
const TokenMap KeywordTokens =
{
    {"not", TokenType::Operator_Not},
    {"div", TokenType::Operator_Div},
    {"mod", TokenType::Operator_Modulo},
    
    {"var", TokenType::Keyword_Var},

    
    // modifiers
    {"init",TokenType::Keyword_Init},
    {"call",TokenType::Keyword_Call},
    {"global",TokenType::Keyword_Global},
    {"local",TokenType::Keyword_Local},
    {"const",TokenType::Keyword_Const},
    {"copy",TokenType::Keyword_Copy},
    {"ref",TokenType::Keyword_Ref},
    {"in",TokenType::Keyword_In},
    {"out",TokenType::Keyword_Out},
    {"inout",TokenType::Keyword_InOut},
    
    // flow
    {"proc", TokenType::Keyword_Proc},
    {"endproc", TokenType::Keyword_ProcEnd},
    {"program", TokenType::Keyword_Program},
    {"endprogram", TokenType::Keyword_ProgramEnd},
    {"if", TokenType::Keyword_Condition},
    {"endif", TokenType::Keyword_ConditionEnd},
    {"while", TokenType::Keyword_While},
    {"endwhile", TokenType::Keyword_WhileEnd},
    {"do", TokenType::Keyword_Do},
    {"break", TokenType::Keyword_Break},
    {"skip", TokenType::Keyword_Continue},
    {"returns", TokenType::Keyword_Return},
    
    
    {"true", TokenType::Keyword_True},
    {"false", TokenType::Keyword_False}
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
    Token(TokenType type) { Init(type, ""); };
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
        if(token._value.size() == 0)
            stream << "[" << token._type << "]";
        else
            stream << "[" << token._type << "," << token._value << "]";
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
