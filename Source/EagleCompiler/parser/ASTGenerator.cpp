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
#include "../ast/type/CodeType.h"
#include "../ast/type/CodeTypeBoolean.h"
#include "../ast/type/CodeTypeInteger32.h"
#include "../ast/type/CodeTypeString.h"


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


vector<CodeExpression*> ASTGenerator::genCodeExpressionList(SyntaxTree* node){
    vector<CodeExpression*> expressions;

    vector<SyntaxTree*> exprNodes = findAllNonTerminals(node, "EXPR");
    vector<SyntaxTree*> repNodes = findAllNonTerminals(node, "REPEXPR");
    // concat the two lists
    exprNodes.insert( exprNodes.end(), repNodes.begin(), repNodes.end() );
    
    for (int i=0; exprNodes.size() > i; i++) {
        CodeExpression* expr = genExpression(exprNodes[i]);
        expressions.push_back(expr);
    }
    
    return expressions;
};


CodeStatement* ASTGenerator::genCodeStatement(SyntaxTree* cmdNode){
    CodeStatement* statement = NULL;
    vector<SyntaxTree*> cmdChilds = cmdNode->getChildren();
    
    /*
     terminal SKIP
        SKIP
     terminal LPAREN
        <expr> BECOMES <expr>
     terminal ADDOPR
        <expr> BECOMES <expr>
     terminal NOT
        <expr> BECOMES <expr>
     terminal IDENT
        <expr> BECOMES <expr>
     terminal LITERAL
        <expr> BECOMES <expr>
     terminal IF
        IF <expr> THEN <cpsCmd> ELSE <cpsCmd> ENDIF
     terminal WHILE
        WHILE <expr> DO <cpsCmd> ENDWHILE
     terminal CALL
        CALL IDENT <exprList> <optGlobInitList>
     terminal DEBUGIN
        DEBUGIN <expr>
     terminal DEBUGOUT
        DEBUGOUT <expr>
     */
    
    SyntaxTree* nextTerminal = findNextTerminalRec(cmdNode);
    if(nextTerminal != NULL)
    {
        switch (nextTerminal->getToken()->getType()) {
            case TokenType::Keyword_Continue:
            {
                statement = new CodeSkipStatement();
            }
                break;
                
            case TokenType::Operator_Assignment:
            {
                SyntaxTree* lValueNode = cmdChilds[0];
                SyntaxTree* rValueNode = cmdChilds[2];
                
                CodeExpression* lvalue = genExpression(lValueNode);
                CodeExpression* rvalue = genExpression(rValueNode);
                
                CodeExpressionVariable* v = dynamic_cast<CodeExpressionVariable*>(lvalue);
                if(v != 0) {
                    statement = new CodeAssignmentStatement(lvalue, rvalue);
                }else{
                    ostringstream errStr;
                    errStr << "ASTGenerator: Semantic issue: Assignment LValue must be CodeExpressionFactorVariable but was " << lvalue;
                    throw new GrammarException(errStr.str());
                }
            }
                break;
                
            case TokenType::Keyword_While:
            {
                SyntaxTree* conditionNode = cmdChilds[1];
                CodeExpression* condition = genExpression(conditionNode);
                
                CodeWhileStatement* whileStatement = new CodeWhileStatement(condition);
                statement = whileStatement;
                
                SyntaxTree* condStatements = findChildNonTerminal(cmdNode, "CPSCMD");
                vector<CodeStatement*> statements = genCodeStatements(condStatements);
                for (int i=0; statements.size()>i; i++) {
                    whileStatement->addLoopStatement(statements[i]);
                }
                
                break;
            }
            case TokenType::Keyword_Call:
            { //  CALL IDENT <exprList> <optGlobInitList>
                
                CodeProcedure *procedure = NULL;
                
                SyntaxTree* identNode = cmdChilds[1];
                if(identNode->isTerminal() && identNode->getToken()->getType() == TokenType::Identifier){
                    string procName = identNode->getToken()->getValue();
                    procedure = new CodeProcedure(procName);
                }else{
                    throw new GrammarException("ASTGenerator Expected Identifier but got...");
                }
                
                CodeProcedureCallStatement* procCall = new CodeProcedureCallStatement(procedure);
                
                // ExpressionList: expr, expr, expr....
                
                SyntaxTree* exprListNode = cmdChilds[2];
                SyntaxTree* optExprNode = findChildNonTerminal(exprListNode, "OPTEXPR");
                
                vector<CodeExpression*> expressions = genCodeExpressionList(optExprNode);
                
                for (int i=0; expressions.size()>i; i++) {
                    procCall->addParameterExpression(expressions[i]);
                }
            }
                break;
                
            case TokenType::Keyword_Condition:
            { // IF <expr> THEN <cpsCmd> ELSE <cpsCmd> ENDIF
                
                if(cmdChilds.size() >= 7){ // TODO handle ifs without else block
                    SyntaxTree* condExprNode = cmdChilds[1];
                    SyntaxTree* ifCmdsNode = cmdChilds[3];
                    SyntaxTree* elseCmdsNode = cmdChilds[5];
                    
                    CodeExpression* condExpr = genExpression(condExprNode);
                    vector<CodeStatement*> ifStatements = genCodeStatements(ifCmdsNode);
                    vector<CodeStatement*> elseStatements = genCodeStatements(elseCmdsNode);
                    
                    CodeIfStatement* condition = new CodeIfStatement(condExpr);
                    statement = condition;
                    
                    for (int i=0; ifStatements.size()>i; i++) {
                         condition->addIfStatement(ifStatements[i]);
                    }
                    
                    for (int i=0; elseStatements.size()>i; i++) {
                        condition->addElseStatement(elseStatements[i]);
                    }
                }else{
                    throw new GrammarException("ASTGenerator: Missing tokens for valid WHILE command!");
                }
                
            }
                break;
                
            case TokenType::Command_DebugIn:
            {
                SyntaxTree* lValueNode = cmdChilds[1];
                CodeExpression* lvalue = genExpression(lValueNode);
                statement = new CodeInputStatement(lvalue);
            }
                break;
                
            case TokenType::Command_DebugOut:
            {
                SyntaxTree* exprNode = cmdChilds[1];
                CodeExpression* expr = genExpression(exprNode);
                statement = new CodeOutputStatment(expr);
            }
                break;
                
                
            default:
            {
                ostringstream errStr;
                errStr << "ASTGenerator: Command -> Unexpected Token " <<  *nextTerminal->getToken();
                throw new GrammarException(errStr.str());
            }
        }
    }
    return statement;
};

CodeExpression* ASTGenerator::genExpression(SyntaxTree* exprNode){
    
    static int MAX_DEPTH = 30;
    
    CodeExpression* expr = NULL;
    
    // TODO generate expression
    
    /*
    CodeVariable* id = new CodeVariable(nextTerminal->getToken()->getValue(), NULL); // TODO Type???
    CodeExpression* lvalue = new CodeExpressionFactorVariable(id);
    
    if(){
        CodeExpressionFactorInitialize();
    }*/
    
    //SyntaxTree* node = findRecursiveNonTerminal(exprNode, "TERM3", MAX_DEPTH);
    //SyntaxTree* addExpr = findChildNonTerminal(node, "REPADDOPRTERM3");
    
    
    if(exprNode->isTerminal()){
        CodeType* type = NULL;
        if(exprNode->getTerminal()->getName() == "LITERAL")
        {
            // CodeExpressionFactorLiteral(CodeType *type, string value)
            switch(exprNode->getToken()->getType()){
                case TokenType::Literal_Number:
                    type = CodeTypeInteger32::getInstance();
                    break;
                    
                case TokenType::Literal_String:
                    type = CodeTypeString::getInstance();
                    break;
                    
                case TokenType::Literal_True:
                case TokenType::Literal_False:
                    
                    type = CodeTypeBoolean::getInstance();
                    break;
                    
                    default:
                    ostringstream errStr;
                    errStr << "Unknown Literal Type: " << *exprNode->getToken();
                    throw new GrammarException(errStr.str());
                    break;
            }
        }
        expr = new CodeExpressionLiteral(type, exprNode->getToken()->getValue());
    }else{
        // current node is NT
        if(!exprNode->hasChildren()){
            // Empty NT Node
            return NULL;
        }else if(exprNode->getChildren().size() == 1){
            expr = genExpression(exprNode->getChildren()[0]);
        }else{
            
            vector<string> operatorNTs = { "REPADDOPRTERM3", "REPMULTOPRFACTOR" };
            
            // Check for binary Operator nodes
            SyntaxTree* oprNode = NULL;
            for(int i=0;operatorNTs.size()>i;i++){
                oprNode = findChildNonTerminal(exprNode, operatorNTs[i]);
                if(oprNode != NULL && oprNode->getChildren().size() > 1){
                    // Case ADD/MIN node
                    break;
                }else{
                    oprNode = NULL;
                }
            }
            
            if(oprNode != NULL){
                
                SyntaxTree* leftSideExprNode = exprNode->getChildren()[0];
                SyntaxTree* operatorTerminalNode = oprNode->getChildren()[0];
                SyntaxTree* rightSideExprNode = oprNode->getChildren()[1];
                
                if(!operatorTerminalNode->isTerminal()){
                    ostringstream errStr;
                    errStr << "Expected node to be Operator TERMINAL but was: " << *operatorTerminalNode->getNonTerminal() << "\n";
                    throw new GrammarException(errStr.str());
                }
                
                // find now the matching binary operator expression (dydiac expr)
                switch(operatorTerminalNode->getToken()->getType()){
                    case TokenType::Operator_Plus:
                        
                        // TODO
                        //expr = new CodeExpressionAdd(ADDOPERATOR::PLUS, );
                        
                        break;
                        
                    case TokenType::Operator_Minus:
                        
                        break;
                        
                    case TokenType::Operator_Multiply:
                        
                        break;
                        
                    case TokenType::Operator_Div:
                        
                        break;
                        
                    case TokenType::Operator_Modulo:
                        
                        break;
                        
                    case TokenType::Operator_Not:
                        
                        break;
                        
                        default:
                        ostringstream errStr;
                        errStr << "Unhandled Operator-Token: " << *operatorTerminalNode->getToken() << "\n";
                        throw new GrammarException(errStr.str());
                        break;
                        
                }
                
                
                
                
            }

        }
    }
    
    return expr;
};





SyntaxTree* ASTGenerator::findNextTerminalRec(SyntaxTree* parent){
    
    vector<SyntaxTree*> children = parent->getChildren();
    for (int i=0; children.size() > i; i++) {
        SyntaxTree* child = children[i];
        if(child->isTerminal())
            return child;
    }
    
    for (int i=0; children.size() > i; i++) {
        SyntaxTree* child = children[i];
        if(!child->isTerminal())
            return findNextTerminalRec(child);
    }
    
    return NULL;
};


vector<CodeStatement*> ASTGenerator::genCodeStatements(SyntaxTree* node){
    vector<CodeStatement*> statements;
    
    vector<SyntaxTree*> statementNodes = findAllNonTerminals(node, "CMD");
    vector<SyntaxTree*> repNodes = findAllNonTerminals(node, "REPCMD");
    // concat the two lists
    statementNodes.insert( statementNodes.end(), repNodes.begin(), repNodes.end() );
    
    for (int i=0; statementNodes.size() > i; i++) {
        CodeStatement* statement = genCodeStatement(statementNodes[i]);
        statements.push_back(statement);
    }
    
    return statements;
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


vector<SyntaxTree*> ASTGenerator::findAllNonTerminals(SyntaxTree* parent, const string& name){
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