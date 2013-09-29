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



TokenType Scanner::isToken(int start, int end){
    
    // depending on the current state we have diffrnet grammars
    // i.e. Default, LiteralString or Comment grammar...
    
    // for now, we handle only the default grammar:
    
    
    // DEFAULT GRAMMAR
    
    // check if current range is terminal/operator token
    // then check if range is identifier/literal number
    
    //TokenMap_Default.
    
    
    string possibleToken = subStrFromArr(_sourceData, start, end);
    
    TokenMap::const_iterator it = TokenMap_Default.find(possibleToken);
    if(it != TokenMap_Default.end()){
        // found matching token
        
        
        
    }else{
        // no token found
        
        
    }

    
    return TokenType::None;
}




void Scanner::endToken(TokenType type){
    Token* t = new Token(type);
    _tokens->add(*t);
}

