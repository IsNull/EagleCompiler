//
//  TokenList.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__TokenList__
#define __EagleCompiler__TokenList__

#include <iostream>
#include <list>
#include "Token.h"

using namespace std;

class TokenList
{
private:
    list<Token>* _tokens;
    list<Token>::const_iterator _iterator;
    
public:
    
    TokenList(){ _tokens = new list<Token>(); }
    
    void add(Token& t) { _tokens->push_back(t); }
    
    // reset the iterator
    void reset() {
        _iterator = _tokens->begin();
    }
    
    // return the next Token or NULL
    const Token* next();
    
    friend std::ostream& operator<< (std::ostream& stream, const TokenList& tokenList) {
    
        stream << "{";
        
        list<Token>::const_iterator it = tokenList._tokens->begin();

        while (it != tokenList._tokens->end()) {
            stream << *it << ",";
            it++;
        }
        stream << "}";
        
        return stream;
    }
};

#endif /* defined(__EagleCompiler__TokenList__) */
