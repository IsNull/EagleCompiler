//
//  TokenList.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "TokenList.h"


const Token* TokenList::next(){
    if(_iterator != _tokens->end()){
        const Token* t = &*_iterator;
        _iterator++;
        return t;
    }
    return NULL;
}

string TokenList::toString() const {
    
    list<Token>::const_iterator it = _tokens->begin();
    string tokenListStr = "";
    
    while (it != _tokens->end()) {
        tokenListStr += it->toString() + ",";
        it++;
    }
    
    return "{" + tokenListStr + "}";
}