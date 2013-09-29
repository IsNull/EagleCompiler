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

using namespace std;


Scanner::Scanner(){
    _state = ScannerState::Default;
    _tokens = new TokenList();
}





const TokenList* Scanner::scan(string source){
    
    // convert string to char array
    unsigned long len = source.size();
    char *a=new char[len+1];
    a[len]=0;
    memcpy(a,source.c_str(),len);
    
    int tokenStart = 0;
    int tokenEnd = 0;
   
    TokenType currentType = TokenType::None;
    
    
    for (int i=0; i<len; i++) {
        
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



void Scanner::endToken(TokenType type){
    Token* t = new Token(type);
    _tokens->add(*t);
}

