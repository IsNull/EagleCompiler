//
//  Scanner.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//


#include "ScannerContext.h"


using namespace std;

/**
 * Grammar Default grammar implementation
 *
 */
TokenType ScannerContextDefault::stepRange(int start, int end){

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

KnownScannerState ScannerContextDefault::nextState(){
    return KnownScannerState::Default;
};