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
#include "ScannerEnums.h"
#include "../Token.h"
#include "../TokenList.h"
#include "ScannerContext.h"
#include "../Util.h"


using namespace std;



class IScannerContext; // forward declaration


class Scanner {
private:
    IScannerContext* _contextState;  // The current scanner context state
    
    TokenType _currentType;         // the current contexts state, representet as token type
    
    TokenList* _tokens;             // Holds all tokens we gathered so far
    char* _sourceData;              // char buffer for fast accessing the source
    int _sourceSize;                // size of the source char buffer
    
    bool _omitWhiteSpaces = true;
    
    
    void init(string source);
    
    void handleEOF(TokenType rollingToken, int tokenStart, int tokenEnd);

    void endToken(TokenType type, int start, int end);
    
    
    /**
     * Set the ScannerContext of this scanner
     */
    void setContext(KnownScannerState stateType);
    
    /**
     * Determines whats the token type of the current range is.
     * If the current range is no longer a known token, we have found a token t(start,end-1);
     * since one char before we had a token.
     *
     * IMPLEMENTATION NOTE:
     *
     * In the current implementation this call is delegated to the current ScannerContext
     *
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
    
    bool isNumber(int start, int end);
    
    bool isIdentifier(int start, int end);
    
    bool isWhiteSpace(int start, int end);
    
    bool isNewLine(int start, int end);
};




#endif /* defined(__EagleCompiler__Scanner__) */
