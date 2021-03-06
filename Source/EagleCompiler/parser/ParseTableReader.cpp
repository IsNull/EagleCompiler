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

const bool ParseTableReader_DEBUG = false;


const string ParseTableReader::KEYWORD_TERMINAL = "terminal";


const NonTerminal* ParseTableReader::getNonTerminalOrCreate(string name){
    const NonTerminal* foundNonTerminal = NULL;
    
    // ToLowerCase
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    
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
    
    // ToLowerCase
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    
    map<string, const NonTerminal*>::const_iterator it = nonterminals.find(name);
    return (it != nonterminals.end()) ? it->second : NULL;
}

const Terminal* ParseTableReader::getTerminal(string name) const{
    
    // ToLowerCase
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    
    map<string, const Terminal*>::const_iterator it = terminals.find(name);
    return (it != terminals.end()) ? it->second : NULL;
}


const Terminal* ParseTableReader::getTerminalOrCreate(string name){
    const Terminal* foundTerminal = NULL;
    
    // ToLowerCase
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    
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

void printRules(ParseRuleTable* table){
    cout << "ParseRuleTable:\n\n";
    for (ParseRuleTable::const_iterator it = table->begin(), end = table->end(); it != end; ++it) {
        cout << *(it->first) << "\n";
    }
}


Parser* ParseTableReader::createParser(TokenList* tokenlist, string serializedTable){
   
    cout << "\n\nParsing Fix & Foxi Parse-Table:\n\n";
    
    
    ParseRuleTable* parseRuleTable = new ParseRuleTable();
    
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
        
        
        if(line[0] == '<'){
            // First char must be < in order to identify as a NT-Def
            
            state = TableParserState::EXPECT_NONTERM_DEF;
            if(ParseTableReader_DEBUG) cout << "Parsing NT Definition: " << line << "\n";
            unsigned long end = line.find(">");
            if(end != string::npos)
            {
                currentNT = getNonTerminalOrCreate(line.substr(1,end-1));
                currentRule = new ProductionRule(currentNT);
                parseRuleTable->insert(make_pair(currentNT, currentRule));
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
            
            if(ParseTableReader_DEBUG) cout << "terminal decl: " << line << "\n";
            
            string terminalName = words[1];
            currentTerminal = getTerminalOrCreate(terminalName);
            
            state = TableParserState::EXPECT_RULELIST;
            continue; // Next-Line
        }
        
        if(state == TableParserState::EXPECT_RULELIST){
            
            if(ParseTableReader_DEBUG) cout << "rule list: " << line << "\n";
            
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
                        
                        if(symbol != NULL){
                            // add to our current rule
                            prod->push_back(symbol);
                        }else{
                            cout << "ERROR: Can not handle symbol: '" << *wordIt << "'" ;
                        }
                    }
                }
            }
            currentRule->addProduction(currentTerminal, prod);
            state = TableParserState::EXPECT_TERMINAL;
            continue;
        }
        
        cout << "ERROR: Unhandled Line: " << line << "\n";
    }
    cout << "\n--- Parsing Fix&Foxi done. ---\n";
    if(ParseTableReader_DEBUG) printRules(parseRuleTable);
    
    return new Parser(tokenlist, parseRuleTable, this);
}


