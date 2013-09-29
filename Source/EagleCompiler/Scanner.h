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
#include "Token.h"
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
    
    char* _sourceData;
    int _sourceSize;
    
    TokenType _currentType; // holds the current token type
    
    
    void endToken(TokenType type);
    
    bool isNumber(int start, int end);
    bool isIdentifier(int start, int end);
    
    /**
     * Determines whats the token type of the current range is.
     * If the current range is no longer a known token, we have found a token t(start,end-1);
     * since one char before we had a token.
     */
    TokenType isToken(int start, int end);
    
    
public:
    
    Scanner();
    
    const TokenList* scan(string source);
    
    
    
};


#endif /* defined(__EagleCompiler__Scanner__) */
