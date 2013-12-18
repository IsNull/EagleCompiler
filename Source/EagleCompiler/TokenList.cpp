//
//  TokenList.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "TokenList.h"


const Token* TokenList::stepNext() {
    if(_iterator != _tokens.end()){
        const Token* t = *_iterator;
        _iterator++;
        return t;
    }
    return NULL;
}

