//
//  Scanner.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//


#include "ScannerContext.h"


using namespace std;

//
// ============================= ScannerContextDefault =============================
//

/*
 * Tokenmap for the default context.
 * Contains all tokens which have to be detected in this context
 * (for comments or literal strings, there are diffrent contexts)
 */
const TokenMap TokenMap_Default =
{
    {";", TokenType::StatementEnd},
    
    // Comments
    {"/*", TokenType::Comment_ML_Start},
    {"*/", TokenType::Comment_ML_End},
    {"//", TokenType::Comment_Line},
    
    // Operators
    {"=", TokenType::Operator_Equals},
    {"+", TokenType::Operator_Plus},
    {"-", TokenType::Operator_Minus},
    {":=", TokenType::Operator_Assignment},
    {">", TokenType::Operator_GreaterThan},
    {"<", TokenType::Operator_SmallerThan},
    {">=", TokenType::Operator_GreaterThanOrEqual},
    {"<=", TokenType::Operator_SmallerThanOrEqual},
    {"*", TokenType::Operator_Multiply},
    {"/", TokenType::Operator_Div},
    {"!", TokenType::Operator_Not},
    {"&", TokenType::Operator_StringConcat},
    
    // Brackets
    {"(", TokenType::Bracked_Round_Open},
    {")", TokenType::Bracked_Round_Close},
    {"{", TokenType::Bracked_Curly_Open},
    {"}", TokenType::Bracked_Curly_Close},
    {"[", TokenType::Bracked_Square_Open},
    {"]", TokenType::Bracked_Square_Close}
};

/*
 * Tokenmap for the multi comment context.
 * Contains all tokens which have to be detected in this context
 */
const TokenMap TokenMap_MlComment =
{
    {"*/", TokenType::Comment_ML_End}
};


/**
 * Grammar Default grammar implementation
 *
 */
TokenType ScannerContextDefault::stepRangeInternal(int start, int end){


    // Check if current range is terminal/operator token
    TokenType rangeTokenType = lookupToken(start, end, TokenMap_Default);
    
    // no simple token found. Check if its a Number or Identifier

    
    if(rangeTokenType == TokenType::None){
        // we could not find a matching token in our context map
        // we have to check for identifiers and literals by ourselfes:
        
        if(_scanner->isNumber(start, end))
        {
            rangeTokenType = TokenType::LiteralNumber;
        }else if(_scanner->isIdentifier(start, end)){
            rangeTokenType = TokenType::Identifier;
        }else if(_scanner->isWhiteSpace(start, end)){
            rangeTokenType = TokenType::WhiteSpace;
        }else if(_scanner->isNewLine(start, end)){
            rangeTokenType = TokenType::NewLine;
        }
    }
    
    return rangeTokenType;
};

KnownScannerState ScannerContextDefault::mapNextState(TokenType token){
    switch (token) {
        case TokenType::Comment_Line:
            return KnownScannerState::LineComment;
            break;
            
        case TokenType::Comment_ML_Start:
            return KnownScannerState::MultiLineComment;
            break;
            
        case TokenType::LiteralString:
            return KnownScannerState::LiteralString;
            break;
            
        default:
            // Every other token won't change the current state
            // thus we keep the default state
            return KnownScannerState::Default;
            break;
    }
};


//
// ============================= ScannerContextLineComment =============================
//

TokenType ScannerContextLineComment::stepRangeInternal(int start, int end){
    
    TokenType rangeTokenType = TokenType::None;
    
    if(_scanner->isNewLine(start, end)){
        rangeTokenType = TokenType::NewLine;
    }else if(!_scanner->isNewLine(end, end)){ // check if last char is NOT NewLine
        rangeTokenType = TokenType::Comment_Line;
    }
    
    return rangeTokenType;
};


KnownScannerState ScannerContextLineComment::mapNextState(TokenType token){
    switch (token) {
        case TokenType::NewLine:
            return _previousContext;
            break;
            
        default:
            // Every other token won't change the current state
            // thus we keep the default state
            return KnownScannerState::LineComment;
            break;
    }
};





//
// ============================= ScannerContextMultiLineComment =============================
//

TokenType ScannerContextMultiLineComment::stepRangeInternal(int start, int end){
    
    TokenType rangeTokenType = lookupToken(start, end, TokenMap_MlComment);
    
    return rangeTokenType;
};


KnownScannerState ScannerContextMultiLineComment::mapNextState(TokenType token){
    switch (token) {
        case TokenType::Comment_ML_End:
            return _previousContext;
            break;
            
        default:
            // Every other token won't change the current state
            // thus we keep the default state
            return KnownScannerState::MultiLineComment;
            break;
    }
};

