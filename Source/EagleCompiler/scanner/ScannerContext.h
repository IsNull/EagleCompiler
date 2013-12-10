//
//  Scanner.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__ScannerContext__
#define __EagleCompiler__ScannerContext__

#include <iostream>
#include <string>
#include "../Token.h"
#include "Scanner.h"
#include "../Singleton.h"
#include "ScannerEnums.h"

using namespace std;


class Scanner; // forward decl

/**
 * Represents a scanner context interface
 */
class IScannerContext {
public:
    
    
    virtual ~IScannerContext() {}
    
    /**
     * Set the external info for this state.
     */
    virtual void startContext(Scanner* scanner, KnownScannerState previousContext) = 0;
    
    
    /**
     * Analyzes the given string and yields a Token.
     * Also, after each stepRange, the nextState property is updated.
     *
     */
    virtual TokenType stepRange(int start, int end) = 0;
    
    /**
     * Returns the next state type which should be used.
     * This may be any state, some situations depend on the previous state.
     *
     * The value depends on preceding yielded tokens by stepRange
     */
    virtual KnownScannerState nextState() = 0;
    
    
    /**
     * Get the ScannerState value corresponding to this StateContext
     */
    virtual KnownScannerState getState() = 0;
    
};


class ScannerContextBase  : public IScannerContext {

protected:
    Scanner* _scanner;
    KnownScannerState _previousContext;
    KnownScannerState _nextState;
    
    // To be implemented by concrete sub classes
    virtual TokenType stepRangeInternal(int start, int end)=0;
    virtual KnownScannerState mapNextState(TokenType token)=0;
    
public:
    /**
     * Set the external info for this state.
     */
    void startContext(Scanner* scanner, KnownScannerState previousContext){
        _scanner = scanner;
        _previousContext = previousContext;
    }
    
    TokenType lookupToken(int start, int end, TokenMap map){
        
        TokenType rangeTokenType = TokenType::None;

        string possibleToken = _scanner->range(start, end);
        
        
        TokenMap::const_iterator it = map.find(possibleToken);
        
        if(it != map.end()){
            // found matching token
            rangeTokenType = it->second;
        }
        
        return rangeTokenType;
    };
    
    TokenType stepRange(int start, int end){
        TokenType token = stepRangeInternal(start, end);
        _nextState = mapNextState(token);
        return token;
    };
    
    KnownScannerState nextState(){ return _nextState; };
};

/**
 * Represents the default scanner context. (Basic statements, code structure)
 */
class ScannerContextDefault  : public ScannerContextBase, public Singleton <ScannerContextDefault>{
    
    friend class Singleton <ScannerContextDefault>;
    
public:
    ~ScannerContextDefault () { };
    
    //
    // IScannerContext implementation
    //
    
    TokenType stepRangeInternal(int start, int end);
    KnownScannerState mapNextState(TokenType token);
    KnownScannerState getState() { return KnownScannerState::Default; }
    
protected:
    ScannerContextDefault(){ };
    
};


/**
 * Represents the LineComment scanner context.
 */
class ScannerContextLineComment  : public ScannerContextBase, public Singleton <ScannerContextLineComment>{
    
    friend class Singleton <ScannerContextLineComment>;
    
public:
    ~ScannerContextLineComment () { };
    
    //
    // IScannerContext implementation
    //
    
    TokenType stepRangeInternal(int start, int end);
    KnownScannerState mapNextState(TokenType token);
    KnownScannerState getState() { return KnownScannerState::LineComment; }
    
protected:
    ScannerContextLineComment(){ };
    
};

/**
 * Represents the MultiLineComment scanner context.
 */
class ScannerContextMultiLineComment  : public ScannerContextBase, public Singleton <ScannerContextMultiLineComment>{
    
    friend class Singleton <ScannerContextMultiLineComment>;
    
public:
    ~ScannerContextMultiLineComment () { };
    
    //
    // IScannerContext implementation
    //
    
    TokenType stepRangeInternal(int start, int end);
    KnownScannerState mapNextState(TokenType token);
    KnownScannerState getState() { return KnownScannerState::LineComment; }
    
protected:
    ScannerContextMultiLineComment(){ };
    
};


/**
 * Represents the LiteralString scanner context.
 */
class ScannerContextLiteralString  : public ScannerContextBase, public Singleton <ScannerContextLiteralString>{
    
    friend class Singleton <ScannerContextLiteralString>;
    
public:
    ~ScannerContextLiteralString () { };
    
    //
    // IScannerContext implementation
    //
    
    TokenType stepRangeInternal(int start, int end);
    KnownScannerState mapNextState(TokenType token);
    KnownScannerState getState() { return KnownScannerState::LineComment; }
    
protected:
    ScannerContextLiteralString(){ };
    
};

//


/**
 *ScannerContextLiteralStringExpression
 * Represents the LiteralStringExpression scanner context.
 */
class ScannerContextLiteralStringExpression  : public ScannerContextBase, public Singleton <ScannerContextLiteralStringExpression>{
    
    friend class Singleton <ScannerContextLiteralStringExpression>;
    
public:
    ~ScannerContextLiteralStringExpression() { };
    
    //
    // IScannerContext implementation
    //
    
    TokenType stepRangeInternal(int start, int end);
    KnownScannerState mapNextState(TokenType token);
    KnownScannerState getState() { return KnownScannerState::LineComment; }
    
protected:
    ScannerContextLiteralStringExpression(){ };
    
};


#endif /* defined(__EagleCompiler__ScannerContext__) */
