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



class ParseTableReader
{
    
private:
    static const string KEYWORD_TERMINAL;

    map<string, NonTerminal*> nonterminals;
    map<string, Terminal*> terminals;
    
    const NonTerminal* getNonTerminal(string name);
    const Terminal* getTerminal(string name);
    
    TokenType findTokenByParserName(string parserName);
    
public:
    /**
     * Creates a syntax parser from the given parse table
     */
    Parser createParser(TokenList tokenlist, string serializedTable);
};



#endif /* defined(__EagleCompiler__ParseTableReader__) */
