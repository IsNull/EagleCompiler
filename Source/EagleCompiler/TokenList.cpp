//
//  TokenList.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "TokenList.h"


const Token* TokenList::stepNext() {
    
    const Token* current = NULL;
    
    if(_tokens.size() > _pos){
        current = _tokens[_pos];
        _pos++;
    }
    return current;
}

