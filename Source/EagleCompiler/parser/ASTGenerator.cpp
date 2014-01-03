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


CodeProcedureDeclaration* ASTGenerator::genProcedureDecl(SyntaxTree* procDeclNode){
    // NODE := PROCDECL
    CodeProcedureDeclaration* procDecl = NULL;
    
    // TODO
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
        vector<CodeParameter*> params = genCodeParameter(procParamListNode);
        for (int i=0; params.size() > i; i++) {
            procDecl->addParam(params[i]);
        }
    }
    
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


// TODO

vector<CodeDeclaration*> ASTGenerator::genCodeDeclarations(SyntaxTree* node){
    vector<CodeDeclaration*> decls;
    
    vector<SyntaxTree*> childs = node->getChildren();
    for (int i=0; childs.size() > i; i++) {
        
        SyntaxTree* procDeclNode = findRecursiveNonTerminal(childs[i], "PROCDECL");
        if(procDeclNode != NULL)
        {
            CodeProcedureDeclaration* procDecl = genProcedureDecl(procDeclNode);
            decls.push_back(procDecl);
        }
        
        // TODO other decls?
        
    }
    
    return decls;
};

vector<CodeParameter*> ASTGenerator::genCodeParameter(SyntaxTree* node){
    vector<CodeParameter*> params;
    
    // TODO
    
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

CodeProgram* ASTGenerator::generate(SyntaxTree* syntaxParseTree){
    
    SyntaxTree* node = syntaxParseTree;
    CodeProgram* program = new CodeProgram();
    
    // extract prog param list
    SyntaxTree* progParamList = findChildNonTerminal(node, "PROGPARAMLIST");
    if(progParamList != NULL)
    {
        vector<CodeParameter*> params = genCodeParameter(progParamList);
        for (int i=0; params.size() > i; i++) {
            program->addProgParam(params[i]);
        }
    }
    
    // extract decls
    SyntaxTree* gobalDecls = findChildNonTerminal(node, "OPTGLOBALCPSDECL");
    if(gobalDecls != NULL)
    {
        vector<CodeDeclaration*> params = genCodeDeclarations(progParamList);
        for (int i=0; params.size() > i; i++) {
            program->addGlobalDecl(params[i]);
        }
    }
    
    // extract Statements
    SyntaxTree* cmdNode = findChildNonTerminal(node, "CPSCMD");
    if(cmdNode != NULL)
    {
        vector<CodeStatement*> statements = genCodeStatements(cmdNode);
        for (int i=0; statements.size() > i; i++) {
            program->addProgStatement(statements[i]);
        }
    }
    
    return program;
};