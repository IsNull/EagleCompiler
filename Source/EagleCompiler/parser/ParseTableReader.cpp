//
//  ParseTableReader.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 14.12.13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "ParseTableReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

const string ParseTableReader::KEYWORD_TERMINAL = "terminal";

vector<string> split(const string& s, const string& delim, const bool keep_empty = true);


const NonTerminal* ParseTableReader::getNonTerminal(string name){
    NonTerminal* foundNonTerminal;
    map<string, NonTerminal*>::const_iterator it = nonterminals.find(name);
    
    if(nonterminals.end() == it){
        foundNonTerminal = new NonTerminal(name);
        nonterminals.insert(make_pair(name, foundNonTerminal));
    }else{
        foundNonTerminal = it->second;
    }
    
    return foundNonTerminal;
}


TokenType ParseTableReader::findTokenByParserName(string parserName){
    // TODO Implement!
    cout << "TODO: Implement ParseTableReader::findTokenByParserName!";
    return TokenType::None;
}

const Terminal* ParseTableReader::getTerminal(string name){
    Terminal* foundTerminal;
    map<string, Terminal*>::const_iterator it = terminals.find(name);
    
    if(terminals.end() == it){
        // create a new Terminal
        TokenType type = findTokenByParserName(name);
        foundTerminal = new Terminal(name, type);
        terminals.insert(make_pair(name, foundTerminal));
    }else{
        foundTerminal = it->second;
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
    vector<string> lines = split(serializedTable,"\n");
    
    for (std::vector<string>::iterator it = lines.begin() ; it != lines.end(); ++it){
        
        string line = *it;
        
        unsigned long start = line.find("<");
        
        if(start == 0){
            state = TableParserState::EXPECT_NONTERM_DEF;
            cout << "Parsing NT Definition: " << line << "\n";
            unsigned long end = line.find(">");
            
            if(start != string::npos && end != string::npos)
            {
                currentNT = getNonTerminal(line.substr(start+1,end-1));
                currentRule = new ProductionRule(currentNT);
            }else
                cout << "Unexpected sign while parsing Parse-Table. Line: " << lineNum;
            
            state = TableParserState::EXPECT_TERMINAL;
            continue; // Next-Line
        }
        
        unsigned long terminalStart = line.find(KEYWORD_TERMINAL);
        
        if(terminalStart){
            // we found a terminal decl
            vector<string> words = split(line," ", false);
            
            cout << "terminal decl: " << line << "\n";
            for (std::vector<string>::iterator wordIt = words.begin() ; wordIt != words.end(); ++wordIt){
                cout << "word: " << &wordIt << "\n";
            }
            
            string terminalName = words[1];
            currentTerminal = getTerminal(terminalName);
            
            state = TableParserState::EXPECT_RULELIST;
            continue; // Next-Line
        }
        
        lineNum++;
    }
    
    Parser parser = Parser(tokenlist, parseRuleTable);
    return parser;
}


/**
 * Split the given string by the given delemiter into a string-vector
 */
vector<string> split(const string& s, const string& delim, const bool keep_empty) {
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}