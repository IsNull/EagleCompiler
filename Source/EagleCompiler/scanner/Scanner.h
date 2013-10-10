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
#include <string>
#include "Token.h"
#include "TokenList.h"

using namespace std;


/**
 * Represents a basic state of the scanner
 * for diffrent grammar contexts
 */
enum class ScannerState {
    Default,            // default context
    LineComment,        // the scanner is in a line comment context
    MultiLineComment,   // the scanner is in a multiline comment context
    LiteralString       // the scanner is in literal string context
};


class Scanner {
private:
    ScannerState _state;    // The scanner context state
    TokenType _currentType; // the current contexts state, representet as token type
    
    TokenList* _tokens;     // Holds all tokens we gathered so far
    char* _sourceData;      // char buffer for fast accessing the source
    int _sourceSize;        // size of the source char buffer
    
    bool _omitWhiteSpaces = true;
    
    
    void init(string source);
    
    void handleEOF(TokenType rollingToken, int tokenStart, int tokenEnd);

    void endToken(TokenType type, int start, int end);
    
    bool isNumber(int start, int end);
    
    bool isIdentifier(int start, int end);
    
    bool isWhiteSpace(int start, int end);
    
    /**
     * Determines whats the token type of the current range is.
     * If the current range is no longer a known token, we have found a token t(start,end-1);
     * since one char before we had a token.
     */
    TokenType isToken(int start, int end);
    
    
public:
    
    Scanner();
    
    /**
     * Scan the given source and return a TokenList
     *
     */
    const TokenList* scan(string source);
    
    /**
     * Get the source string of the given range
     */
    string range(int start, int end);
};


#endif /* defined(__EagleCompiler__Scanner__) */
