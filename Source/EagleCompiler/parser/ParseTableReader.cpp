//
//  ParseTableReader.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 14.12.13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "ParseTableReader.h"
#include "../Util.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

const string ParseTableReader::KEYWORD_TERMINAL = "terminal";


const NonTerminal* ParseTableReader::getNonTerminalOrCreate(string name){
    const NonTerminal* foundNonTerminal = NULL;
    
    if(name.size() > 0){
        foundNonTerminal = getNonTerminal(name);

        if(foundNonTerminal == NULL){
            foundNonTerminal = new NonTerminal(name);
            nonterminals.insert(make_pair(name, foundNonTerminal));
        }
    }
    return foundNonTerminal;
}

const NonTerminal* ParseTableReader::getNonTerminal(string name) const{
    map<string, const NonTerminal*>::const_iterator it = nonterminals.find(name);
    return (it != nonterminals.end()) ? it->second : NULL;
}

const Terminal* ParseTableReader::getTerminal(string name) const{
    map<string, const Terminal*>::const_iterator it = terminals.find(name);
    return (it != terminals.end()) ? it->second : NULL;
}


const Terminal* ParseTableReader::getTerminalOrCreate(string name){
    const Terminal* foundTerminal = NULL;
    
    if(name.size() > 0){
        foundTerminal = getTerminal(name);
    
        if(foundTerminal == NULL){
            foundTerminal = new Terminal(name);
            terminals.insert(make_pair(name, foundTerminal));
        }
    }
    return foundTerminal;
}

/**
 * parse <nonterminal>
 */
const NonTerminal* ParseTableReader::parseNonterminal(string ntString){
    const NonTerminal* nt = NULL;
    unsigned long start = ntString.find("<");
    if(start == 0){
        unsigned long end = ntString.find(">");
        
        if(start != string::npos && end != string::npos)
        {
            nt = getNonTerminalOrCreate(ntString.substr(start+1,end-1));
        }
    }
    
    return nt;
};


Parser* ParseTableReader::createParser(TokenList* tokenlist, string serializedTable){
   
    
    cout << "\n\nParsing Fix & Foxi Parse-Table:\n\n";
    
    
    ParseRuleTable parseRuleTable;
    
    // Table-Parser States
    TableParserState state = TableParserState::EXPECT_NONTERM_DEF;
    
    const NonTerminal* currentNT;
    ProductionRule* currentRule;
    
    const Terminal* currentTerminal;
    
    
    int lineNum = 0;
    vector<string> lines = Util::split(serializedTable,"\n");
    
    cout << "found " << lines.size() << " lines in serialized table. \n\n";
    
    
    for (std::vector<string>::iterator it = lines.begin() ; it != lines.end(); ++it){
        lineNum++;
        string line = *it;
        
        unsigned long start = line.find("<");
        
        if(start != string::npos){
            state = TableParserState::EXPECT_NONTERM_DEF;
            cout << "Parsing NT Definition: " << line << "\n";
            unsigned long end = line.find(">");
            
            if(start != string::npos && end != string::npos)
            {
                currentNT = getNonTerminalOrCreate(line.substr(start+1,end-1));
                currentRule = new ProductionRule(currentNT);
            }else
                cout << "Unexpected sign while parsing Parse-Table. Line: " << lineNum;
            
            state = TableParserState::EXPECT_TERMINAL;
            continue; // Next-Line
        }
        
        // Parse terminal decl
        unsigned long terminalStart = line.find(KEYWORD_TERMINAL);
        if(terminalStart != string::npos){
            // we found a terminal decl
            vector<string> words = Util::split(line," ", false);
            
            cout << "terminal decl: " << line << "\n";
            
            string terminalName = words[1];
            currentTerminal = getTerminalOrCreate(terminalName);
            
            state = TableParserState::EXPECT_RULELIST;
            continue; // Next-Line
        }
        
        if(state == TableParserState::EXPECT_RULELIST){
            
            Production* prod = NULL;
            // expect rule list
            vector<string> ruleSymbols = Util::split(line," ", false);
            
            if(ruleSymbols.size() > 0){
                prod = new Production();

                for (std::vector<string>::iterator wordIt = ruleSymbols.begin() ; wordIt != ruleSymbols.end(); ++wordIt){
                    if(wordIt->size() > 0){
                        const IGrammarSymbol* symbol;
                        symbol = parseNonterminal(*wordIt);
                        if(symbol == NULL){
                            symbol = getTerminalOrCreate(*wordIt);
                        }
                        // add to our current rule
                        prod->push_back(symbol);
                    }
                }
            }
            currentRule->addProduction(currentTerminal, prod);
            state = TableParserState::EXPECT_TERMINAL;
        }
    }
    return new Parser(*tokenlist, parseRuleTable, this);
}


