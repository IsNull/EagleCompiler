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
    virtual void consume(TokenType expectedToken)=0;
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
    
    friend std::ostream& operator<< (std::ostream& stream, const IGrammarSymbol& symbol) {
        stream << symbol.name;
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
    TokenType tokenType;
public:
    Terminal(string name, TokenType type){
        this->name = name;
        this->tokenType = type;
    }
    
    bool isTerminal() const { return true; }
    
    TokenType getTokenType() const { return tokenType; }
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
    list<SyntaxTree> _children;
    
    
public:
    SyntaxTree(const IGrammarSymbol* symbol)
        :_grammarSymbol(symbol)
    {
    }
    
    list<SyntaxTree> getChildren() { return _children; }
    bool hasChildren() const { return _children.size() != 0; }
    void add(const SyntaxTree& node){ _children.push_back(node); }
    
    bool isTerminal() const {
        return _grammarSymbol->isTerminal();
    }
    
    NonTerminal* getNonTerminal() const { return (NonTerminal*)_grammarSymbol; }
    Terminal* getTerminal() const { return (Terminal*)_grammarSymbol; }
};



// ==========================================


/* Represents a production rule map */
typedef list<IGrammarSymbol*> Production;
typedef map<const Terminal*, Production> ProductionMap;

class IProductionRule {
    virtual SyntaxTree produce(IParseContext ctx)=0;
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
    
    void addProduction(Terminal* terminal, Production production){
        productionTable.insert(make_pair(terminal, production));
    };
    
    SyntaxTree produce(IParseContext ctx){
        SyntaxTree node(nonterminal);
        
        const Token* currentToken = ctx.current();
        const Terminal* currentTerminal = ctx.getTerminal(currentToken->getType()); // TODO Get Terminal from current token?
        
        ProductionMap::const_iterator productionit = productionTable.find(currentTerminal);
        if(productionit != productionTable.end()){
            // found matching production
            Production production = productionit->second;
            
            for (Production::const_iterator it = production.begin(), end = production.end(); it != end; ++it) {
                IGrammarSymbol* s = *it;
                
                if(s->isTerminal()){
                    Terminal *t = (Terminal*)s;
                    ctx.consume(t->getTokenType());
                    
                    node.add(SyntaxTree(t)); // TODO add Token to SyntaxTree for later analysis
                }else{
                    NonTerminal *nt = (NonTerminal*)s;
                    // look-up  ProductionRule for this nt
                    ProductionRule* rule = ctx.getRule(nt);
                    if(rule != NULL){
                        SyntaxTree subtree = rule->produce(ctx);
                        node.add(subtree);
                    }
                }
                
            }
            
        }else{
            cout << "Current Token has no rule in this Production Rule!";
        }
        
        return node;
    };
};

typedef map<const NonTerminal*, ProductionRule*> ParseRuleTable;

class Parser : public IParseContext
{
private:
    TokenList _tokenlist;
    const ParseRuleTable _ruleMap;
    const Token* _current;
    
public:
    
    Parser(TokenList& tokenlist, ParseRuleTable& parseTable)
    : _tokenlist(tokenlist) , _ruleMap(parseTable){
        _current = _tokenlist.stepNext();
    }
    
    void consume(TokenType expectedToken){
        
        if(_current == NULL)
        {
            ostringstream errStr;
            errStr << "ERROR: Unexpected EOF in Token List. Expected Token: "  << expectedToken;
            throw new GrammarException(errStr.str());
        }
        
        if(_current->getType() == expectedToken){
            // the expected token is present
           _current = _tokenlist.stepNext();
        }else{
            ostringstream errStr;
            errStr << "ERROR: Unexpected Token: '" << _current << "' expected: "  << expectedToken;
            throw new GrammarException(errStr.str());
        }
    }
    
    const Token* current() const { return _current; }
    
    ProductionRule* getRule(const NonTerminal* nt){
        ProductionRule* rule = NULL;
        
        ParseRuleTable::const_iterator it = _ruleMap.find(nt);
        if(it == _ruleMap.end()){
            rule = it->second;
        }else{
            cout << "No Rule found for NT: " << nt;
            // TODO Handle error / implement rule
        }
        return rule;
    }
    
    const Terminal* getTerminal(TokenType expectedToken){
        // TODO Implement mapping!!
        cout << "Parser::getTerminal: TODO Implement mapping!! ";
        return NULL;
    }
    
};

#endif /* defined(__EagleCompiler__Parser__) */
