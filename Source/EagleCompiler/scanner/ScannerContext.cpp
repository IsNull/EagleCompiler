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
    // Note that Comment_ML_End is not detected in this context
    {"//", TokenType::Comment_Line},
    
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


/**
 * Grammar Default grammar implementation
 *
 */
TokenType ScannerContextDefault::stepRangeInternal(int start, int end){

    TokenType rangeTokenType = TokenType::None;
    
    string possibleToken = _scanner->range(start, end);
    
    
    // Check if current range is terminal/operator token
    // then check if range is identifier/literal number
    
    TokenMap::const_iterator it = TokenMap_Default.find(possibleToken);
    
    if(it != TokenMap_Default.end()){
        // found matching token
        rangeTokenType = it->second;
    }
    
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

// TODO



//
// ============================= ScannerContextMultiLineComment =============================
//

// TODO

