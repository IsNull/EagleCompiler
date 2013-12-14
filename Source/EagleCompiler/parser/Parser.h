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
#include <string>
#include "../TokenList.h"
#include "../Token.h"

// forward decls
class ProductionRule;
class NonTerminal;


class IParseContext
{
public:
    virtual void consume(TokenType expectedToken)=0;
    virtual TokenType current()=0;
    virtual ProductionRule getRule(NonTerminal nt)=0;
};


/**
 * Represents a Grammar Symbol such as {Terminal, NonTerminal}
 */
class IGrammarSymbol
{
public:
    virtual bool isTerminal()=0;
};

/**
 * Represents a terminal symbol representet by a single token
 *
 */
class Terminal  : public IGrammarSymbol
{
private:
    Token* token;
    
public:
    Terminal(Token* token){
        this->token = token;
    }
    bool isTerminal(){ return true; }
    
    TokenType getTokenType() { return token->getType(); }
};

/**
 * Represents a logical NonTerminal
 */
class NonTerminal  : public IGrammarSymbol
{
public:
    // TODO: Save name? String or Enum?
    NonTerminal(){
        
    }
    bool isTerminal(){ return false; }
};



// ==========================================

/**
 * Simple Syntax Tree structure
 * This class represents nodes as well as leafes which avoids casting / polymorhism
 */
class SyntaxTree
{
private:
    IGrammarSymbol* symbol;
    list<SyntaxTree> children;
    
    
public:
    SyntaxTree(IGrammarSymbol& symbol){
        this->symbol = &symbol;
    }
    
    list<SyntaxTree> getChildren();
    bool hasChildren() { return children.size() != 0; }
    void add(SyntaxTree node){ children.push_back(node); }
    
    bool isTerminal(){
       return symbol->isTerminal();
    }
    
    NonTerminal* getNonTerminal(){ return (NonTerminal*)symbol; }
    Terminal* getTerminal(){ return (Terminal*)symbol; }
};



// ==========================================


/* Represents a production rule map */
typedef list<IGrammarSymbol*> Production;
typedef map<Terminal, Production> ProductionMap;

class IProductionRule {
    virtual SyntaxTree produce(IParseContext ctx)=0;
};

/**
 * Represents a single production rule which belongs
 * To a given nonterminal
 */
class ProductionRule : public IProductionRule {
private:
    NonTerminal nonterminal;
    ProductionMap productionTable;
    
public:
    ProductionRule(NonTerminal nonterm, ProductionMap production){
        nonterminal = nonterm;
        productionTable = production;
    }
    
    SyntaxTree produce(IParseContext ctx){
        SyntaxTree node(nonterminal);
        
        Token token = ctx.current();
        Terminal term; // TODO from current token?
        
        ProductionMap::const_iterator productionit = productionTable.find(term);
        if(productionit != productionTable.end()){
            // found matching production
            Production production = productionit->second;
            
            for (Production::const_iterator it = production.begin(), end = production.end(); it != end; ++it) {
                IGrammarSymbol* s = *it;
                
                if(s->isTerminal()){
                    Terminal t = *((Terminal*)s);
                    ctx.consume(t.getTokenType());
                    node.add(SyntaxTree(t));
                }else{
                    NonTerminal nt = *((NonTerminal*)s);
                    // look-up  ProductionRule for this nt
                    ProductionRule rule = ctx.getRule(nt);
                    SyntaxTree subtree = rule.produce(ctx);
                    node.add(subtree);
                }
                
                
            }
            
        }else{
            cout << "Current Token has no rule in this Production Rule!";
        }

        
        
        return node;
    };
};


class Parser : public IParseContext
{
private:
    TokenList tokenlist;
    map<NonTerminal, ProductionRule> ruleMap;
    
public:
    
    Parser(TokenList tokenlist);
    
    void consume(TokenType expectedToken);
    
    TokenType current();
    
    ProductionRule getRule(NonTerminal nt){
        map<NonTerminal, ProductionRule>::const_iterator it = ruleMap.find(nt);
        if(it == ruleMap.end()){
            return it->second;
        }
        // TODO Handle error
    }
    
};

#endif /* defined(__EagleCompiler__Parser__) */
