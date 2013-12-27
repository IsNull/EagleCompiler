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
#include <vector>
#include "Token.h"

using namespace std;

class TokenList
{
private:
    vector<const Token*> _tokens;
    int _pos = 0;
    
public:
    
    TokenList(){ }
    
    void add(const Token* t) { _tokens.push_back(t); }
    
    // reset the iterator
    void reset() {
        _pos = 0;
    }
    
    // return the next Token or NULL
    const Token* stepNext();
    
    friend std::ostream& operator<< (std::ostream& stream, const TokenList& tokenList) {
        
        stream << "{";
        
        vector<const Token*>::const_iterator it = tokenList._tokens.begin();
        
        while (it != tokenList._tokens.end()) {
            stream << **it << ",";
            it++;
        }
        stream << "}";
        
        return stream;
    }};

#endif /* defined(__EagleCompiler__TokenList__) */
