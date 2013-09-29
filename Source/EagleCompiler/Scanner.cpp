//
//  Scanner.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Scanner.h"
#include "Token.h"
#include "TokenList.h"
#include "Util.h"
#include <cctype>

using namespace std;


Scanner::Scanner(){
    _state = ScannerState::Default;
    _tokens = new TokenList();
}



const TokenList* Scanner::scan(string source){
    
    // convert string to char array
    _sourceSize = (int)source.size();
    _sourceData = new char[_sourceSize+1];
    _sourceData[_sourceSize]=0;
    memcpy(_sourceData,source.c_str(),_sourceSize);
    
    int tokenStart = 0; // points to the start of the current Token
    int tokenEnd = 0;   // points to the end of the current Token
   
    
    _currentType = TokenType::None;
    
    
    for (int i=0; i<_sourceSize; i++) {
        
        switch (_state) {
            case ScannerState::Default:
                

                // TODO
                break;
                
            case ScannerState::MultiLineComment:
                //TODO
                break;
                
            case ScannerState::LiteralString:
                // TODO
                break;
                
            default:
                // exception No state handling
                break;
        }
    }
    
    
    return _tokens;
}


/**
 * Determines the token type of the given range (in the given context)*
 *  
 * Returns a token type if the whole range has been identified as a token
 * or TokenType::None if the range is not a valid token
 *
 * TODO(*)
 */
TokenType Scanner::isToken(int start, int end){
    
    TokenType rangeTokenType = TokenType::None;
    
    string possibleToken = subStrFromArr(_sourceData, start, end);
    
    // Depending on the current state we have diffrnet grammars
    // i.e. Default, LiteralString or Comment grammar...
    
    // for now, we handle only the default grammar:
    
    
    // ---- STATE: DEFAULT GRAMMAR ---- (TODO: Refactor into state pattern)
    
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
        
        if(isNumber(start, end))
        {
            rangeTokenType = TokenType::LiteralNumber;
        }else if(isIdentifier(start, end)){
            rangeTokenType = TokenType::Identifier;
        }
    }
    
    // ---- END STATE: DEFAULT GRAMMAR ----
    
    return rangeTokenType;
}


bool Scanner::isNumber(int start, int end){
    
    char* cp = _sourceData + (sizeof(char) * start);
    int len = end-start+1;
    
    for (int i=0; i<len; i++) {
        if(!isdigit(*cp))
            return false;
        cp++;
    }
    
    return true;
}

/**
 * Checks if the given char range is an valid Identifier
 * 
 * Valid identiviers must start with an alpha and then continue with alpha-num.
 *
 * abc
 * ab1
 *
 */
bool Scanner::isIdentifier(int start, int end){
    
    char* cp = _sourceData + (sizeof(char) * start);
    int len = end-start+1;
    
    for (int i=0; i<len; i++) {
        
        if(i==0 && !isalpha(*cp))
            return false;
        else if( i != 0 && !isalnum(*cp))
            return false;
        cp++;
    }
    
    return true;
}

void Scanner::endToken(TokenType type){
    Token* t = new Token(type);
    _tokens->add(*t);
}

