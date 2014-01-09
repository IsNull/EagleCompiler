//
//  Util.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__Parser__
#define __EagleCompiler__Parser__

#include <iostream>
#include <sstream>
#include <string>
#include "../TokenList.h"
#include "../Token.h"

// forward decls
class ProductionRule;
class Terminal;
class NonTerminal;


/**
 * Represents the parse context
 */
class IParseContext
{
public:
    virtual void consume(const Terminal* terminal)=0;
    virtual const Token* current() const =0;
    virtual ProductionRule* getRule(const NonTerminal* nt)=0;
    
    virtual const Terminal* getTerminal(TokenType expectedToken)=0;
};

class GrammarException: public exception
{
private:
    string _message;
    
public:
    
    GrammarException(string message){
        this->_message = message;
    }
    
    virtual const char* what() const throw()
    {
        return _message.c_str();
    }
};


/**
 * Represents a Grammar-Symbol such as a {Terminal, NonTerminal}
 */
class IGrammarSymbol
{
protected:
    string name;
    
public:
    virtual bool isTerminal() const =0;
    
    string getName() const { return name; }
    
    friend std::ostream& operator<< (std::ostream& stream, const IGrammarSymbol& symbol) {
        stream << symbol.getName();
        return stream;
    }
};

/**
 * Represents a terminal symbol representet by a single token
 *
 */
class Terminal  : public IGrammarSymbol
{
private:
   // TokenType tokenType;
public:
    Terminal(string name){
        this->name = name;
    }
    
    bool isTerminal() const { return true; }
};

/**
 * Represents a logical NonTerminal
 */
class NonTerminal  : public IGrammarSymbol
{
public:
    NonTerminal(string name){
        this->name = name;
    }
    bool isTerminal() const { return false; }
};



// ==========================================

/**
 * Simple Syntax Tree structure
 * This class represents nodes as well as leafes which avoids casting / polymorhism
 */
class SyntaxTree
{
private:
    const IGrammarSymbol* _grammarSymbol;
    const Token* _token;
    vector<SyntaxTree*> _children;
    
    
public:
    SyntaxTree(const IGrammarSymbol* symbol)
        :_grammarSymbol(symbol), _token(NULL)
    {
    }
    
    SyntaxTree(const IGrammarSymbol* symbol, const Token* _token)
    :_grammarSymbol(symbol), _token(_token)
    {
    }
    
    vector<SyntaxTree*> getChildren() { return _children; }
    bool hasChildren() const { return _children.size() != 0; }
    void add(SyntaxTree* node){ _children.push_back(node); }
    void remove(SyntaxTree* node){
        _children.erase(
                        std::remove(_children.begin(), _children.end(), node), _children.end()
                        );
    }
    
    bool isTerminal() const {
        return _grammarSymbol->isTerminal();
    }
    
    NonTerminal* getNonTerminal() const { return (NonTerminal*)_grammarSymbol; }
    Terminal* getTerminal() const { return (Terminal*)_grammarSymbol; }
    const Token* getToken() const { return _token; }
    
    
    std::ostream& prettyPrint(std::ostream& stream, int level) const {

        for (int i=0; level > i; i++) { stream << "\t"; }
        
        stream << (!this->isTerminal() ? "[" : "") << *(this->_grammarSymbol) << (!this->isTerminal() ? "]" : "");
        if(this->isTerminal()) stream << " " << *this->getToken();
        stream << "\n";
        
        int sublevel = level + 1;
        for (int i=0; this->_children.size() > i; i++) {
            SyntaxTree* child = this->_children[i];
            child->prettyPrint(stream, sublevel);
        }
        
        return stream;
    };
    
    friend std::ostream& operator<< (std::ostream& stream, const SyntaxTree& node) {
        return node.prettyPrint(stream, 0);
    }
};



// ==========================================


/* Represents a production rule map */
typedef list<const IGrammarSymbol*> Production;
typedef map<const Terminal*, Production*> ProductionMap;

class IProductionRule {
    virtual SyntaxTree* produce(IParseContext* ctx)=0;
};

/**
 * Represents a single production rule which belongs
 * To a given nonterminal
 */
class ProductionRule : public IProductionRule {
private:
    const NonTerminal* nonterminal;
    ProductionMap productionTable;
    
public:
    ProductionRule(const NonTerminal *nonterm)
        : nonterminal(nonterm){
    }
    
    void addProduction(const Terminal* terminal, Production* production){
        productionTable.insert(make_pair(terminal, production));
    };
    
    SyntaxTree* produce(IParseContext* ctx);
    
    
    friend std::ostream& operator<< (std::ostream& stream, const ProductionRule& rule) {
        stream << "ProductionRule[" << *(rule.nonterminal) << ": { ";
        
        for (ProductionMap::const_iterator it = rule.productionTable.begin(), end = rule.productionTable.end(); it != end; ++it) {
            stream << *(it->first) << " ";
        }
        stream << "}";
        // ProductionMap Size:" << rule.productionTable.size() << "]";
        return stream;
    }
    
};

typedef map<const NonTerminal*, ProductionRule*> ParseRuleTable;


class IGrammarRepository
{
public:
    /**
     * Returns the NonTerminal with the given Name or NULL if not available
     */
    virtual const NonTerminal* getNonTerminal(string name) const = 0;
    
    /**
     * Returns the Terminal with the given Name or NULL if not available
     */
    virtual const Terminal* getTerminal(string name) const = 0;
};


/**
 *
 */
class Parser : public IParseContext
{
private:
    TokenList* _tokenlist;
    map<const string, TokenType> terminalMap;
    const ParseRuleTable* _ruleMap;
    const Token* _current;
    const IGrammarRepository* _grammarRepository;
    
    bool isMatchingToken(const Terminal* terminal, const Token* token);
    
    void buildTerminalMap(){
        for (map<TokenType, const string>::const_iterator it = TokenNames.begin(), end = TokenNames.end(); it != end; ++it) {
            terminalMap.insert(make_pair(it->second, it->first));
        }
    }
    
public:
    
    Parser(TokenList* tokenlist, ParseRuleTable* parseTable, const IGrammarRepository* grammarRepository)
    :
    _tokenlist(tokenlist),
    _ruleMap(parseTable),
    _grammarRepository(grammarRepository)
    {
        _current = _tokenlist->stepNext();
        buildTerminalMap();
    }
    
    /**
     * Parse the Tokenlist into a SyntaxTree
     */
    SyntaxTree* parse();
    
    /**
     * Consumes the current (expected) terminal
     */
    void consume(const Terminal* terminal);
    
    /**
     * Returns the current Token
     */
    const Token* current() const { return _current; }
    
    ProductionRule* getRule(const NonTerminal* nt);
    
    /**
     * Maps a given TokenType to a Terminal
     * Note that there are multiple TokenTypes which yield the same Terminal
     *
     * I.e. Terminal RELOPR which has several comparision operators
     * RELOPER_EQ, RELOPR_NE etc.
     */
    const Terminal* getTerminal(TokenType expectedToken);
    
};

#endif /* defined(__EagleCompiler__Parser__) */
