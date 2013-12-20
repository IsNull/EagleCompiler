//
//  ParseTableReader.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 14.12.13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "ParseTableReader.h"
#include "Util.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

const string ParseTableReader::KEYWORD_TERMINAL = "terminal";


const NonTerminal* ParseTableReader::getNonTerminalOrCreate(string name){
    const NonTerminal* foundNonTerminal = getNonTerminal(name);
    
    if(foundNonTerminal == NULL){
        foundNonTerminal = new NonTerminal(name);
        nonterminals.insert(make_pair(name, foundNonTerminal));
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
    const Terminal* foundTerminal = getTerminal(name);
    
    if(foundTerminal == NULL){
        // create a new Terminal
        foundTerminal = new Terminal(name);
        terminals.insert(make_pair(name, foundTerminal));
    }
    
    return foundTerminal;
}


Parser ParseTableReader::createParser(TokenList tokenlist, string serializedTable){
   
    
    ParseRuleTable parseRuleTable;
    
    // Table-Parser States
    TableParserState state = TableParserState::EXPECT_NONTERM_DEF;
    
    const NonTerminal* currentNT;
    ProductionRule* currentRule;
    
    const Terminal* currentTerminal;
    Production* currentProduction;
    
    
    int lineNum = 1;
    vector<string> lines = Util::split(serializedTable,"\n");
    
    for (std::vector<string>::iterator it = lines.begin() ; it != lines.end(); ++it){
        
        string line = *it;
        
        unsigned long start = line.find("<");
        
        if(start == 0){
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
        
        unsigned long terminalStart = line.find(KEYWORD_TERMINAL);
        
        if(terminalStart){
            // we found a terminal decl
            vector<string> words = Util::split(line," ", false);
            
            cout << "terminal decl: " << line << "\n";
            for (std::vector<string>::iterator wordIt = words.begin() ; wordIt != words.end(); ++wordIt){
                cout << "word: " << &wordIt << "\n";
            }
            
            string terminalName = words[1];
            currentTerminal = getTerminalOrCreate(terminalName);
            
            state = TableParserState::EXPECT_RULELIST;
            continue; // Next-Line
        }
        
        lineNum++;
    }
    
    Parser parser = Parser(tokenlist, parseRuleTable, this);
    return parser;
}


