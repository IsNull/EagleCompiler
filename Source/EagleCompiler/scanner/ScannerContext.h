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
#include "Token.h"
#include "Scanner.h"

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
    virtual void startContext(Scanner* scanner, ScannerState previousContext) = 0;
    
    
    /**
     * Analyzes the given string an yields a Token.
     * Also, after each stepRange, the nextState property is updated.
     *
     */
    virtual TokenType stepRange(int start, int end) = 0;
    
    /**
     * Returns the next state type which should be used
     */
    virtual ScannerState nextState() = 0;
    
};


class ScannerContextBase  : public IScannerContext {

protected:
    Scanner* _scanner;
    ScannerState _previousContext;

public:
    /**
     * Set the external info for this state.
     */
    void startContext(Scanner* scanner, ScannerState previousContext){
        _scanner = scanner;
        _previousContext = previousContext;
    }
};


class ScannerContextDefault  : public ScannerContextBase {
    
    // IScannerContext implementation
    TokenType stepRange(int start, int end);
    ScannerState nextState();
};





#endif /* defined(__EagleCompiler__ScannerContext__) */
