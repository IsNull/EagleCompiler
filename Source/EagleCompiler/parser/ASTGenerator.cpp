//
//  ASTGenerator.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 14.12.13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "ASTGenerator.h"
#include <string>
#include <vector>
#include "CodeType.h"
#include "CodeTypeBoolean.h"
#include "CodeTypeInteger32.h"
#include "CodeTypeString.h"


CodeProcedureDeclaration* ASTGenerator::genProcedureDecl(SyntaxTree* procDeclNode){
    // NODE := PROCDECL
    CodeProcedureDeclaration* procDecl = NULL;
    CodeProcedure* procedure = NULL;
    
    SyntaxTree* procNameNode = findChildTerminal(procDeclNode, TokenType::Identifier);
    if(procNameNode != NULL)
    {
        string name = procNameNode->getToken()->getValue();
        procedure = new CodeProcedure(name);
    }else
        throw GrammarException("CodeProcedureDeclaration missing Procedure Name (Identifier)!");
    
    procDecl = new CodeProcedureDeclaration(procedure);
    
    // add procedure params
    SyntaxTree* procParamListNode = findChildNonTerminal(procDeclNode, "PARAMLIST");
    if(procParamListNode != NULL)
    {
        vector<CodeParameter*> params = genCodeParameters(procParamListNode);
        for (int i=0; params.size() > i; i++) {
            procDecl->addParam(params[i]);
        }
    }else
        throw GrammarException("CodeProcedureDeclaration missing Procedure PARAMLIST!");

    
    // add procedure local imports
    SyntaxTree* procImportListNode = findChildNonTerminal(procDeclNode, "OPTGLOBIMPLIST");
    if(procImportListNode != NULL)
    {
        // TODO
    }
    
    
    // add procedure local storeage decls
    SyntaxTree* procStorageListNode = findChildNonTerminal(procDeclNode, "OPTCPSSTODECL");
    if(procStorageListNode != NULL)
    {
        // TODO
    }
    

    // add procedure statements
    SyntaxTree* cmdNode = findChildNonTerminal(procDeclNode, "CPSCMD");
    if(cmdNode != NULL)
    {
        vector<CodeStatement*> statements = genCodeStatements(cmdNode);
        for (int i=0; statements.size() > i; i++) {
            procDecl->addStatement(statements[i]);
        }
    }
    
    return procDecl;
};


vector<CodeDeclaration*> ASTGenerator::genCodeDeclarations(SyntaxTree* node){
    vector<CodeDeclaration*> decls;
    
    // PROCDECL
    
    vector<SyntaxTree*> procDeclNodes = findAllNonTerminalRec(node, "PROCDECL");
    cout << "found " << procDeclNodes.size() << " PROCDECL!\n";
    for (int i=0; procDeclNodes.size() > i; i++) {
        CodeProcedureDeclaration* procDecl = genProcedureDecl(procDeclNodes[i]);
        decls.push_back(procDecl);
    }
    
    
    // TODO: Other decls (functions etc)
    
    return decls;
};


/**
 * Parse a parameter into AST
 *
 * Expected Tree-Structure of paramNode:
 *
 *[PARAM]
 *  [OPTFLOWMODE]
 *      FLOWMODE
 *  [OPTMECHMODE]
 *      MECHMODE
 *  [OPTCHANGEMODE]
 *      CHANGEMODE
 *  [TYPEDIDENT]
 *      IDENT
 *      COLON
 *      ATOMTYPE
 *
 */
CodeParameter* ASTGenerator::genCodeParameter(SyntaxTree* paramNode){
    
    FLOWMODE flowMode = FLOWMODE::EMPTY;
    MECHMODE mechMode = MECHMODE::EMPTY;
    CHANGEMODE changeMode = CHANGEMODE::EMPTY;
    
    CodeVariable* variable = NULL;
    
    // FLOWMODE (opt)
    
    SyntaxTree* flowModeNode = findChildNonTerminal(paramNode, "OPTFLOWMODE");
    if(flowModeNode != NULL && flowModeNode->hasChildren())
    {
        SyntaxTree* fmN = flowModeNode->getChildren()[0];
        TokenType flowModeType = fmN->getToken()->getType();
        
        switch (flowModeType) {
            case TokenType::Keyword_In:
                flowMode = FLOWMODE::IN;
                break;
                
            case TokenType::Keyword_Out:
                flowMode = FLOWMODE::OUT;
                break;
                
            case TokenType::Keyword_InOut:
                flowMode = FLOWMODE::INOUT;
                break;
            default:
                throw new GrammarException("ASTGenerator: Unexpected node, expected Flowmode token!");
                break;
        }
    }
    
    // MECHMODE (opt)
    
    SyntaxTree* mechModeNode = findChildNonTerminal(paramNode, "OPTMECHMODE");
    if(mechModeNode != NULL && mechModeNode->hasChildren())
    {
        SyntaxTree* mmN = mechModeNode->getChildren()[0];
        TokenType mechModeType = mmN->getToken()->getType();
        
        switch (mechModeType) {
            case TokenType::Keyword_Copy:
                mechMode = MECHMODE::COPY;
                break;
                
            case TokenType::Keyword_Ref:
                mechMode = MECHMODE::REF;
                break;
                
            default:
                throw new GrammarException("ASTGenerator: Unexpected node, expected Mechmode token!");
                break;
        }
    }
    
    // CHANGEMODE (opt)
    
    SyntaxTree* changeModeNode = findChildNonTerminal(paramNode, "OPTCHANGEMODE");
    if(changeModeNode != NULL && changeModeNode->hasChildren())
    {
        SyntaxTree* cmN = changeModeNode->getChildren()[0];
        TokenType changeModeType = cmN->getToken()->getType();
        
        switch (changeModeType) {
            case TokenType::Keyword_Var:
                changeMode = CHANGEMODE::VAR;
                break;
                
            case TokenType::Keyword_Const:
                changeMode = CHANGEMODE::CONST;
                break;
                
            default:
                throw new GrammarException("ASTGenerator: Unexpected node, expected Changemode token!");
                break;
        }
    }
    
    
    // TYPEDIDENT (required)
    
    // [TYPEDIDENT]
    //      IDENT
    //      COLON
    //      ATOMTYPE
    SyntaxTree* typeIdentNode = findChildNonTerminal(paramNode, "TYPEDIDENT");
    if(typeIdentNode != NULL && typeIdentNode->hasChildren())
    {
        string paramName = "";
        CodeType* paramType = NULL;
        
        
        SyntaxTree* identNode = findChildTerminal(typeIdentNode, TokenType::Identifier);
        if(identNode != NULL){
            paramName = identNode->getToken()->getValue();
            cout << "param: " << paramName << ", ";
        }else
            throw new GrammarException("ASTGenerator: CodeParameter Missing Identifier!");
        
        
        SyntaxTree* typeNode = findChildTerminal(typeIdentNode, "ATOMTYPE");
        if(typeNode != NULL){
            paramType = genCodeType(typeNode);
        }else
            throw new GrammarException("ASTGenerator: CodeParameter Missing AtomType!");
        
        variable = new CodeVariable(paramName, paramType);
        
    }else{
        throw new GrammarException("ASTGenerator: CodeParameter could not be created, missing TYPEDIDENT NT!");
    }
    
    CodeParameter* parameter = new CodeParameter(flowMode, mechMode, changeMode, variable);
    
    return parameter;
}

CodeType* ASTGenerator::genCodeType(SyntaxTree* atomTypeNode){
    
    CodeType* codeType = NULL;
    
    TokenType type = atomTypeNode->getToken()->getType();
    switch (type) {
            
        case TokenType::Type_Int:
            codeType = CodeTypeInteger32::getInstance();
            break;
        case TokenType::Type_Bool:
            codeType = CodeTypeBoolean::getInstance();
            break;
            
        case TokenType::Type_String:
            codeType = CodeTypeString::getInstance();
            break;
            
        default:
            ostringstream errStr;
            errStr << "ASTGenerator: Unknown Code-Type: " << *atomTypeNode->getToken() << " node was " << *atomTypeNode;

            throw new GrammarException(errStr.str());
            break;
    }
    return codeType;
};


vector<CodeParameter*> ASTGenerator::genCodeParameters(SyntaxTree* node){
    vector<CodeParameter*> params;
    
    // Program and procedure / metodh params have different NT names but are actually the same
    // we just inject the correct NT Name here to reuse this method in all cases
    const string paramId = (node->getNonTerminal()->getName()  == "PROGPARAMLIST") ? "PROGPARAM" : "PARAM";
    
    vector<SyntaxTree*> paramNodes = findAllNonTerminalRec(node, paramId, false /*dont search nested*/);
    
    cout << "ASTGenerator::genCodeParameters: " << paramId << ", found " << paramNodes.size() << " param Nodes\n";
    
    for(int i=0; paramNodes.size() > i; i++){
        SyntaxTree* child = paramNodes[i];
        params.push_back(genCodeParameter(child));
    }
    
    cout << "\n";
    
    return params;
};

vector<CodeStatement*> ASTGenerator::genCodeStatements(SyntaxTree* node){
    vector<CodeStatement*> params;
    
    // TODO
    
    return params;
};

SyntaxTree* ASTGenerator::findRecursiveNonTerminal(SyntaxTree* parent, const string& name, int maxDeepth){
    SyntaxTree* match = NULL;
    
    match = findChildNonTerminal(parent, name);
    
    if(match == NULL && parent->hasChildren() && maxDeepth > 0)
    {
        vector<SyntaxTree*> children = parent->getChildren();
        for (int i=0; children.size() > i; i++) {
            match = findRecursiveNonTerminal(children[i], name, maxDeepth-1);
        }
    }
    
    return match;
}

/**
 * Searches in all children of the given parent for a NON Terminal with the given Name
 * (NON Recursive!)
 */
SyntaxTree* ASTGenerator::findChildNonTerminal(SyntaxTree* parent, const string& name){
    for (int i=0; parent->getChildren().size() > i; i++) {
        SyntaxTree* child = parent->getChildren()[i];
        if(!child->isTerminal() && child->getNonTerminal()->getName() == name)
        {
            return child;
        }
    }
    return NULL;
};

/**
 * Searches in all children of the given parent for a Terminal with the given TokenType
 * (Non Recursive)
 */
SyntaxTree* ASTGenerator::findChildTerminal(SyntaxTree* parent, const TokenType tokenType){
    for (int i=0; parent->getChildren().size() > i; i++) {
        SyntaxTree* child = parent->getChildren()[i];
        if(child->isTerminal() && child->getToken()->getType() == tokenType)
        {
            return child;
        }
    }
    return NULL;
};

SyntaxTree*  ASTGenerator::findChildTerminal(SyntaxTree* parent, const string terminalName){
    for (int i=0; parent->getChildren().size() > i; i++) {
        SyntaxTree* child = parent->getChildren()[i];
        if(child->isTerminal() && child->getTerminal()->getName() == terminalName)
        {
            return child;
        }
    }
    return NULL;
}

vector<SyntaxTree*> ASTGenerator::findAllNonTerminalRec(SyntaxTree* parent, const string& name, bool searchNested){
    vector<SyntaxTree*> matches;
    
    if(parent->hasChildren())
    {
        vector<SyntaxTree*> children = parent->getChildren();
        
        SyntaxTree* child;
        for (int i=0; children.size() > i; i++) {
            child = children[i];
            
            if(!child->isTerminal()){
                if(child->getNonTerminal()->getName() == name){
                    matches.push_back(child);
                    if(!searchNested) continue; // we have a match in this child. Should we look for nested matches?
                }
                
                vector<SyntaxTree*> subMatches = findAllNonTerminalRec(child, name, searchNested);
                for(int j=0; subMatches.size() > j; j++){
                    matches.push_back(subMatches[j]);
                }
            }
            
        }
    }
    
    return matches;
};

CodeProgram* ASTGenerator::generate(SyntaxTree* syntaxParseTree){
    
    SyntaxTree* node = syntaxParseTree;
    CodeProgram* program = new CodeProgram();
    
    // extract prog param list
    SyntaxTree* progParamList = findChildNonTerminal(node, "PROGPARAMLIST");
    if(progParamList != NULL)
    {
        vector<CodeParameter*> params = genCodeParameters(progParamList);
        
        cout << "found PROGPARAMLIST with " << params.size() << " params.\n";
        
        for (int i=0; params.size() > i; i++) {
            program->addProgParam(params[i]);
        }
    }else{
        throw new GrammarException("Missing PROGPARAMLIST!");
    }
    
    // extract decls
    SyntaxTree* gobalDecls = findChildNonTerminal(node, "OPTGLOBALCPSDECL");
    if(gobalDecls != NULL)
    {
        vector<CodeDeclaration*> params = genCodeDeclarations(gobalDecls);
        for (int i=0; params.size() > i; i++) {
            program->addGlobalDecl(params[i]);
        }
    }else{
        throw new GrammarException("Missing OPTGLOBALCPSDECL!");
    }
    
    // extract Statements
    SyntaxTree* cmdNode = findChildNonTerminal(node, "CPSCMD");
    if(cmdNode != NULL)
    {
        vector<CodeStatement*> statements = genCodeStatements(cmdNode);
        for (int i=0; statements.size() > i; i++) {
            program->addProgStatement(statements[i]);
        }
    }else{
          throw new GrammarException("Missing CPSCMD!");
    }
    
    return program;
};