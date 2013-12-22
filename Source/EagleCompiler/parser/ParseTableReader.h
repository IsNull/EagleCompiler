//
//  ParseTableReader.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 14.12.13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__ParseTableReader__
#define __EagleCompiler__ParseTableReader__

#include <iostream>
#include <string>
#include "Parser.h"

using namespace std;

enum class TableParserState {
    EXPECT_NONTERM_DEF, // <nonterm>
    EXPECT_TERMINAL,    // terminal ...
    EXPECT_RULELIST,    // <some> FUN <other> <other>
};



class ParseTableReader : public IGrammarRepository
{
    
private:
    static const string KEYWORD_TERMINAL;

    map<string, const NonTerminal*> nonterminals;
    map<string, const Terminal*> terminals;
    
    const NonTerminal* getNonTerminalOrCreate(string name);
    const Terminal* getTerminalOrCreate(string name);
    const NonTerminal* parseNonterminal(string ntString);
    
public:
    /**
     * Creates a syntax parser from the given parse table
     */
    Parser createParser(TokenList tokenlist, string serializedTable);
    
    //
    // IGrammarRepository Implementation:
    //
    
    /**
     * Returns the NonTerminal with the given Name or NULL if not available
     */
    virtual const NonTerminal* getNonTerminal(string name) const;
    
    /**
     * Returns the Terminal with the given Name or NULL if not available
     */
    virtual const Terminal* getTerminal(string name) const;
};



#endif /* defined(__EagleCompiler__ParseTableReader__) */
