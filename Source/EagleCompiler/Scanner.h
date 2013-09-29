//
//  Scanner.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__Scanner__
#define __EagleCompiler__Scanner__

#include <iostream>
#include "TokenList.h"

using namespace std;

enum class ScannerState {
    Default,
    LineComment,        // the scanner is in a line comment //
    MultiLineComment,   // the scanner is in a multiline comment /* */
    LiteralString // the scanner is in literal string
};


class Scanner {
private:
    ScannerState _state;
    TokenList* _tokens;
    
    void endToken(TokenType type);
    
public:
    
    Scanner();
    
    const TokenList* scan(string source);
    
    
    
};


#endif /* defined(__EagleCompiler__Scanner__) */
