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
        _iterator++;
        return &*_iterator;
    }
    return NULL;
}

string TokenList::toString() const {
    return "toString not implemented!";
}