//
//  ParserModel.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 17/10/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__ParserModel__
#define __EagleCompiler__ParserModel__

#include <iostream>
#include <string>
#include <map>
#include "Token.h"


using namespace std;

/**
 * Base class for Grammar parts, such as Terminal and NonTerminal Symbol
 */
class GrammarSymbol
{
    
    friend std::ostream& operator<< (std::ostream& stream, const GrammarSymbol& grammarItem) {
        stream << "[>GrammarSymbol<]";
        return stream;
    }
};


class Terminal : public GrammarSymbol
{
private:
    TokenType _token;

public:
    Terminal(TokenType token){ _token = token; }
    
    
    friend std::ostream& operator<< (std::ostream& stream, const Terminal& terminal) {
        stream << "[" << terminal._token << "]";
        return stream;
    }
};


class NonTerminal : public GrammarSymbol
{
private:
    string _name;
    
public:
    
    bool operator <(const NonTerminal& nonTerminal) const
    {
        return _name < nonTerminal._name;
    }

    
    friend std::ostream& operator<< (std::ostream& stream, const NonTerminal& nonterminal) {
        stream << "{" << nonterminal._name << "}";
        return stream;
    }
};

/**
 * A production is a list of GrammarSymbols
 */
typedef list<GrammarSymbol> Production;

typedef map<TokenType, Production> TokenProductionMap;


/**
 * Represents a row in a parser table
 */
class ProductionRule
{
private:
    NonTerminal _leftSide;
    TokenProductionMap _tokenProductions;
    
public:
    
    ProductionRule(NonTerminal leftSide){
        _leftSide = leftSide;
    }
    
    const NonTerminal getLeftSide() { return _leftSide; }
};


/**
 * Represents the parser table
 */
class ParserTable
{
private:
    map<NonTerminal, ProductionRule> _productionRules;
    
public:
    void AddProductionRule(ProductionRule& rule);
};





#endif /* defined(__EagleCompiler__ParserModel__) */
