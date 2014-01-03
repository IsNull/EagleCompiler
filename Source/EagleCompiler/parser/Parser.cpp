//
//  Util.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Parser.h"
#include "../Util.h"
#include <string>
#include <vector>

#include <string.h> // ???


//
// ============= ProductionRule =============
//


SyntaxTree* ProductionRule::produce(IParseContext* ctx){
    SyntaxTree* node = new SyntaxTree(nonterminal);
    
    cout << "\t-->" << *this << "\n";
    
    const Token* currentToken = ctx->current();
    const Terminal* currentTerminal = ctx->getTerminal(currentToken->getType());
    
    ProductionMap::const_iterator productionit = productionTable.find(currentTerminal);
    if(productionit != productionTable.end()){
        // found matching production
        Production* production = productionit->second;
        
        if(production != NULL){
            for (Production::const_iterator it = production->begin(), end = production->end(); it != end; ++it) {
                const IGrammarSymbol* s = *it;
                
                if(s->isTerminal()){
                    Terminal *t = (Terminal*)s;
                    
                    // DEBUG consume output
                    cout <<  *(this->nonterminal) << "  ";
                    
                    ctx->consume(t); // will throw a GrammarExceptin if current terminal was not expected
                    node->add(new SyntaxTree(t, currentToken));
                    
                }else{
                    NonTerminal *nt = (NonTerminal*)s;
                    // look-up  ProductionRule for this nt
                    ProductionRule* rule = ctx->getRule(nt);
                    if(rule != NULL){
                        SyntaxTree* subtree = rule->produce(ctx);
                        node->add(subtree);
                    }
                }
            }
        }else{
            // an empty production (NULL) means that we have reached the end of this parse sub tree
            cout << "! End of " << *this << "\n";
            //cout << *this << " has no production for requested terminal " << *currentTerminal << "\n";
        }
    }else{
        ostringstream errStr;
        errStr << "Current ProductionRule '" << *this << "' has no production for terminal " << *currentTerminal << "\n";
        throw new GrammarException(errStr.str());
    }
    
    return node;
};


ProductionRule* Parser::getRule(const NonTerminal* nt){
    ProductionRule* rule = NULL;
    
    ParseRuleTable::const_iterator it = _ruleMap->find(nt);
    if(it != _ruleMap->end()){
        rule = it->second;
    }else{
        cout << "No Rule found for NT: '" << *nt << "'. Rule count: " << _ruleMap->size() << "\n";
    }
    return rule;
};



//
// ============= Parser =============
//


bool Parser::isMatchingToken(const Terminal* terminal, const Token* token){
    
    TokenType tokenType = token->getType();
    
    // Find the TokenType for the given terminal:
    
    TokenType terminalType = TokenType::None;
    map<const string, TokenType>::const_iterator it = terminalMap.find(terminal->getName());
    if(it != terminalMap.end()){
        terminalType = it->second;
    }
    
    if(terminalType == TokenType::None){
        ostringstream errStr;
        errStr << "Unknown Terminal "  << *terminal << ", can not map to TokenType.\n";
        throw new GrammarException(errStr.str());
    }
    
    //
    // We have now to handle token groups specally.
    //
    TokenGroupMap::const_iterator grpIt = TokenGroups.find(terminalType);
    if(grpIt != TokenGroups.end()){
        // the terminal was a specail group type, check if a group member matches
        for (list<TokenType>::const_iterator tokIt = grpIt->second.begin(), end = grpIt->second.end(); tokIt != end; ++tokIt) {
            if(*tokIt == tokenType) return true;
        }
        
        ostringstream errStr;
        errStr << "Can not find a mapping for specail group-token: "  << terminalType << ": No group definition for this token.\n";
        throw new GrammarException(errStr.str());
        
    }
    
    return terminalType == tokenType;
};


/**
 * Consumes the current expected terminal
 *
 */
void Parser::consume(const Terminal* expectedTerminal){
    
    if(_current == NULL)
    {
        ostringstream errStr;
        errStr << "ERROR: Unexpected EOF in Token List. Expected Terminal: "  << *expectedTerminal << "\n";
        throw new GrammarException(errStr.str());
    }
    
    if(isMatchingToken(expectedTerminal, _current)){
        // the expected token is present thus we can consume it
        cout << "consumed " << *_current << "\n";
        _current = _tokenlist->stepNext();
    }else{
        // Grammar Error!
        ostringstream errStr;
        errStr << "ERROR: Unexpected Token: '" << *_current << "' Expected Terminal: "  << *expectedTerminal << "\n";
        throw new GrammarException(errStr.str());
    }
};



const Terminal* Parser::getTerminal(TokenType expectedToken){
    
    ostringstream tokenNamestream;
    tokenNamestream << expectedToken;
    string tokenName = tokenNamestream.str();
    
    //
    // In case of a underline, we are only interested in the prefix (group)
    // i.e.: RELOPR_EQ => RELOPR
    //
    if(tokenName.find("_")){
        std::vector<string> parts = Util::split(tokenName, "_");
        tokenName = parts[0];
    }
    
    const Terminal* t = _grammarRepository->getTerminal(tokenName);
    if(t == NULL) cout << "ERROR: No Terminal found for token name: '" << tokenName << "'\n";
    
    return t;
};


SyntaxTree* Parser::parse(){
    // TODO!!!
    
    SyntaxTree* tree = NULL;
    
    string startSymbol = "PROGRAM";
    
    const NonTerminal* program = _grammarRepository->getNonTerminal(startSymbol);
    if(program != NULL){
        ProductionRule* programRule = getRule(program);
        if(programRule != NULL){
            tree = programRule->produce(this);
        }else{
            cout << "Can not find rule for " << *program << "\n";
        }
    }else{
        cout << "Can not find the start symbol " << startSymbol << "\n";
    }
    
    return tree;
};




