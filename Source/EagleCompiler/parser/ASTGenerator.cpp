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
#include <algorithm>
#include "../ast/type/CodeType.h"
#include "../Token.h"


CodeInvokableDeclaration* ASTGenerator::genInvokableDecl(SyntaxTree* procDeclNode, bool isfunction){
    // NODE := PROCDECL or FUNDECL
    
    CodeInvokableDeclaration* invokDecl = NULL;
    
    SyntaxTree* procNameNode = findChildTerminal(procDeclNode, TokenType::Identifier);
    if(procNameNode != NULL)
    {
        string name = procNameNode->getToken()->getValue();
		_context = name + "_";
        if(isfunction){
            
            // check the return storage and add it
            SyntaxTree* retStoDecl = findChildNonTerminal(procDeclNode, "STODECL");
            CodeParameter* codeParam = genCodeParameter(retStoDecl);
            
            if(codeParam != NULL){
                CodeStorageDeclaration* storDecl = new CodeStorageDeclaration(codeParam->getChangeMode(), codeParam->getVariable());
                invokDecl = new CodeFunctionDeclaration(new CodeFunction(name, storDecl->getVariable()->getType()), storDecl);
            }else
                throw new GrammarException("CodeFunctionDeclaration missing return param (STODECL)!");
            
        }else{
            invokDecl = new CodeProcedureDeclaration(new CodeProcedure(name));
        }
    }else
        throw new GrammarException("CodeInvokableDeclaration missing Procedure/Function Name (Identifier)!");
    
    
    
    // add procedure params
    SyntaxTree* procParamListNode = findChildNonTerminal(procDeclNode, "PARAMLIST");
    if(procParamListNode != NULL)
    {
        vector<CodeParameter*> params = genCodeParameters(procParamListNode);
        for (int i=0; params.size() > i; i++) {
            invokDecl->addParam(params[i]);
        }
    }else
        throw GrammarException("CodeProcedureDeclaration missing Procedure PARAMLIST!");

    
    // add procedure local imports
    SyntaxTree* procImportListNode = findChildNonTerminal(procDeclNode, "OPTGLOBIMPLIST");
    if(procImportListNode != NULL)
    {
        // TODO
    }
    
    
    // add storeage decls
    SyntaxTree* procStorageListNode = findChildNonTerminal(procDeclNode, "OPTCPSSTODECL");
    if(procStorageListNode != NULL)
    {
        vector<SyntaxTree*> stoDecls = findAllNonTerminalRec(procStorageListNode, "STODECL");
        for(int i=0; stoDecls.size() > i; i++){
            CodeParameter* param = genCodeParameter(stoDecls[i]);
            invokDecl->addLocalStoDecl(new CodeStorageDeclaration(param->getChangeMode(), param->getVariable()));
        }
    }
    
    

    // add procedure statements
    SyntaxTree* cmdNode = findChildNonTerminal(procDeclNode, "CPSCMD");
    if(cmdNode != NULL)
    {
        vector<CodeStatement*> statements = genCodeStatements(cmdNode);
        for (int i=0; statements.size() > i; i++) {
            invokDecl->addStatement(statements[i]);
        }
    }
    
    return invokDecl;
};


vector<CodeDeclaration*> ASTGenerator::genCodeDeclarations(SyntaxTree* node){
    vector<CodeDeclaration*> decls;
    
    // PROCDECL
    
    vector<SyntaxTree*> procDeclNodes = findAllNonTerminalRec(node, "PROCDECL");
    cout << "found " << procDeclNodes.size() << " PROCDECL!\n";
    for (int i=0; procDeclNodes.size() > i; i++) {
        CodeInvokableDeclaration* procDecl = genInvokableDecl(procDeclNodes[i], false);
        decls.push_back(procDecl);
    }
    
    // FUNCDECL
    
    vector<SyntaxTree*> funDeclNodes = findAllNonTerminalRec(node, "FUNDECL");
    cout << "found " << funDeclNodes.size() << " FUNDECL!\n";
    for (int i=0; funDeclNodes.size() > i; i++) {
        CodeInvokableDeclaration* funDecl = genInvokableDecl(funDeclNodes[i], true);
        decls.push_back(funDecl);
    }
    
    _context = "__main__";
    
    // STORAGE DECL
    
    vector<SyntaxTree*> stoDecls = findAllNonTerminalRecExcluding(node, "STODECL", {"FUNDECL", "PROCDECL"});
    cout << "found " << stoDecls.size() << " STODECL!\n";
    for(int i=0; stoDecls.size() > i; i++){
        CodeParameter* param = genCodeParameter(stoDecls[i]);
        decls.push_back(new CodeStorageDeclaration(param->getChangeMode(), param->getVariable()));
    }
    
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
        CodeType paramType = CodeType::UNKNOWN;
        
        
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
		_variables.insert(make_pair(_context+paramName, variable));        
    }else{
        throw new GrammarException("ASTGenerator: CodeParameter could not be created, missing TYPEDIDENT NT!");
    }
    
    CodeParameter* parameter = new CodeParameter(flowMode, mechMode, changeMode, variable);
    
    return parameter;
}

CodeType ASTGenerator::genCodeType(SyntaxTree* atomTypeNode){
    
    CodeType codeType = CodeType::UNKNOWN;
    
    TokenType type = atomTypeNode->getToken()->getType();
    switch (type) {
            
        case TokenType::Type_Int:
            codeType = CodeType::INT32;
            break;
        case TokenType::Type_Bool:
            codeType = CodeType::BOOL;
            break;
            
        case TokenType::Type_String:
            codeType = CodeType::STRING;
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
    vector<SyntaxTree*> repconNodes = findAllNonTerminals(node, "REPCONCOPREXPR");
    
    if(repconNodes.size() > 0)
        cout << "ASTGenerator: found REPCONCOPREXPR " << repconNodes.size();
    
    // concat the two lists
    exprNodes.insert( exprNodes.end(), repNodes.begin(), repNodes.end() );
    exprNodes.insert( repconNodes.end(), repconNodes.begin(), repconNodes.end() );
    
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
    SyntaxTree* nextTerminal = NULL;
    for(int i=0; cmdChilds.size() > i; i++){
        if(cmdChilds[i]->isTerminal()){
            const Token* tok = cmdChilds[i]->getToken();
            if(tok->getType() != TokenType::Semicolon)
                nextTerminal = cmdChilds[i];
            break;
        }
    }
    
    
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
                    errStr << "ASTGenerator: Semantic issue: Assignment LValue must be of type 'CodeExpressionVariable' but was "
                    << ((lvalue != NULL) ? lvalue->toString() : "<null>\n");
                    
                    errStr << "LValue-Node:\n" << *lValueNode;
                    
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
                    procedure = findGlobalProcedure(procName);
                    if(procedure == NULL)
                        throw new GrammarException("AST Error: Usage of undeclared procedure: " + procName);
                    
                }else{
                    throw new GrammarException("ASTGenerator Expected Identifier but got...");
                }
                
                CodeProcedureCallStatement* procCall = new CodeProcedureCallStatement(procedure);
                statement = procCall;
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
                errStr << "ASTGenerator:genCodeStatement Command -> Unexpected Token " <<  *nextTerminal->getToken() << "Cmd Subtree:\n" << *cmdNode;
                throw new GrammarException(errStr.str());
            }
        }
    }
    
    if(statement != NULL)
        cout << "ASTGenerator: Statement: " << statement->toString() << "\n";
    
    return statement;
};

CodeExpression* ASTGenerator::genExpression(SyntaxTree* exprNode){
    
    CodeExpression* expr = NULL;
    
    if(exprNode->isTerminal()){
        
        if(exprNode->getTerminal()->getName() == "LITERAL")
        {
            CodeType type = CodeType::UNKNOWN;
            
            // CodeExpressionFactorLiteral(CodeType *type, string value)
            switch(exprNode->getToken()->getType()){
                case TokenType::Literal_Number:
                    type = CodeType::INT32;
                    break;
                    
                case TokenType::Literal_String:
                    type = CodeType::STRING;
                    break;
                    
                case TokenType::Literal_True:
                case TokenType::Literal_False:
                    
                    type = CodeType::BOOL;
                    break;
                    
                    default:
                    ostringstream errStr;
                    errStr << "Unknown Literal Type: " << *exprNode->getToken();
                    throw new GrammarException(errStr.str());
                    break;
            }
            
            
            expr = new CodeExpressionLiteral(new CodeVariable("_lit_"+to_string((long)exprNode->getToken())+"_", type), exprNode->getToken()->getValue());
        }

    }else{
        // current node is NT
        
        if(!exprNode->hasChildren()){
            // Empty NT Node, means dead end
            return NULL;
        }else if(exprNode->getChildren().size() == 1){
            // Single childs are handled recursive
            expr = genExpression(exprNode->getChildren()[0]);
        }else{
            // Multiple children - check for specail expressions
            // such as BinaryOperators or Function calls
            
            SyntaxTree* firstChild = exprNode->getChildren()[0];
            
            if(firstChild->isTerminal()
               && firstChild->getToken()->getType() == TokenType::Identifier){
                
                SyntaxTree* secondChild = exprNode->getChildren()[1];
                string identifier = firstChild->getToken()->getValue();
                
                if(secondChild->getNonTerminal()->getName() == "IDENTFACTOR"){
                    
                    // this might be either a variable or a function invokation
                    // check if we have an expression list NT
                    if(secondChild->hasChildren()
                       && !secondChild->getChildren()[0]->isTerminal()
                       && secondChild->getChildren()[0]->getNonTerminal()->getName() == "EXPRLIST"){
                        
                        // we have a function call here

                        SyntaxTree* exprListNode = secondChild->getChildren()[0];
                        SyntaxTree* optExprNode = findChildNonTerminal(exprListNode, "OPTEXPR");
                        vector<CodeExpression*> expressions = genCodeExpressionList(optExprNode);
                        
                        CodeFunction* fun = findGlobalFunction(identifier);
                        if(fun != NULL){
                            CodeExpressionFunctionCall* funexpr = new CodeExpressionFunctionCall(fun);
                            expr = funexpr;
                            for (int i=0; expressions.size()>i; i++) {
                                funexpr->addParameter(expressions[i]);
                            }
                        }else
                            throw new GrammarException("AST Exception: Usage of undeclared function: " + firstChild->getToken()->getValue());
                        
                    } else if(secondChild->hasChildren()
                              && secondChild->getChildren()[0]->isTerminal()
                              && secondChild->getChildren()[0]->getToken()->getType() == TokenType::Keyword_Init){
                        
						if(_variables.count(_context+identifier) == 1){
							// it is a init variable reference
							expr = new CodeExpressionInitializeVariable(_variables[_context+identifier]);
						} else {
                            throw new GrammarException("AST Exception: Usage of undeclared variable: " + identifier + " in context " + _context);
						}
                    }else{
						if(_variables.count(_context+firstChild->getToken()->getValue()) == 1){
                        // it is a siple variable reference
                        expr = new CodeExpressionVariable(_variables[_context+firstChild->getToken()->getValue()]);
						} else {
							throw new GrammarException("AST Exception: Usage of undeclared variable: " + identifier + " in context " + _context);
						}
                    }
                }
            }
            
            if(expr == NULL){
                expr = genOperatorExpression(exprNode);
            }
            
            // TODO
            
            if(expr == NULL){
               // for now just fetch the first child-expression which is viable:
                
                for (int i=0; exprNode->getChildren().size() > i; i++) {
                    SyntaxTree* child = exprNode->getChildren()[i];
                    expr = genExpression(child);
                    if(expr != NULL) break;
                }
            }
        }
    }

    
    return expr;
};

CodeFunction* ASTGenerator::findGlobalFunction(const string& name){
    CodeFunction* function = NULL;
    vector<CodeDeclaration*> decls = _program->getGlobalDecl();
    for (int i=0; decls.size() > i; i++) {
        CodeIdentifier* id = decls[i]->getIdentifier();
        if(id->getName() == name){
            function = dynamic_cast<CodeFunction*>(id);
            if(function != NULL) break;
        }
    }
    return function;
};

CodeProcedure* ASTGenerator::findGlobalProcedure(const string& name){
    CodeProcedure* procedure = NULL;
    vector<CodeDeclaration*> decls = _program->getGlobalDecl();
    for (int i=0; decls.size() > i; i++) {
        CodeIdentifier* id = decls[i]->getIdentifier();
        if(id->getName() == name){
            procedure = dynamic_cast<CodeProcedure*>(id);
            if(procedure != NULL) break;
        }
    }
    return procedure;
};

CodeVariable* ASTGenerator::findGlobalVariable(const string& name){
    CodeVariable* variable = NULL;
    vector<CodeDeclaration*> decls = _program->getGlobalDecl();
    for (int i=0; decls.size() > i; i++) {
        CodeIdentifier* id = decls[i]->getIdentifier();
        if(id->getName() == name){
            variable = dynamic_cast<CodeVariable*>(id);
            if(variable != NULL) break;
        }
    }
    return variable;
};


CodeBinaryExpression* ASTGenerator::genBinaryExpression(CodeExpression* leftSideExpr, SyntaxTree* operatorTerminalNode, CodeExpression* rightSideExpr){
    CodeBinaryExpression* binaryExpression = NULL;
    
    if(!operatorTerminalNode->isTerminal()){
        ostringstream errStr;
        errStr << "Expected node to be Operator TERMINAL but was: " << *operatorTerminalNode->getNonTerminal() << "\n";
        throw new GrammarException(errStr.str());
    }
    
    // find now the matching binary operator for binary-expression
    
    TokenType opToken = operatorTerminalNode->getToken()->getType();
    
    map<TokenType, BINARYOPERATOR>::const_iterator findIt =  BINARYOPERATOR_MAP.find(opToken);
    if(findIt != BINARYOPERATOR_MAP.end()){
        BINARYOPERATOR op = findIt->second;
        binaryExpression = new CodeBinaryExpression(leftSideExpr, op, rightSideExpr);
    }else{
        ostringstream errStr;
        errStr << "Unhandled Operator-Token: " << *operatorTerminalNode->getToken() << "\n";
        throw new GrammarException(errStr.str());
    }
    
    return binaryExpression;
};

CodeBinaryExpression* ASTGenerator::genBinaryExpression(CodeExpression* leftSideExpr, SyntaxTree* opNode){
    
    SyntaxTree* opTerminalNode = opNode->getChildren()[0];
    SyntaxTree* rightSideNode = opNode->getChildren()[1];
    CodeExpression* rightSideExpr = genExpression(rightSideNode);
    
    CodeBinaryExpression* expr = genBinaryExpression(leftSideExpr, opTerminalNode, rightSideExpr);
    
    if(opNode->getChildren().size() == 2){
        // we are done
    }else if(opNode->getChildren().size() == 3){
        SyntaxTree* possibleRepNode = opNode->getChildren()[2];
        if(possibleRepNode->hasChildren()){
            // it is a NT with rep Expr -> recurse into!
            CodeBinaryExpression* outerExpr = genBinaryExpression(expr, possibleRepNode);
            if(outerExpr != NULL)
                expr = outerExpr;
        }
    }else{
        // Invalid
        cout << "Error: genBinaryExpression() -> Unexpected node for generating binary expression!\n" << *opNode;
    }

    return expr;
};


CodeExpression* ASTGenerator::genOperatorExpression(SyntaxTree* exprNode){
    
    CodeExpression* opExpression = NULL;
    
    for (int i=0; exprNode->getChildren().size() > i; i++) {
        SyntaxTree* child = exprNode->getChildren()[i];

        if(child->hasChildren() && child->getChildren()[0]->isTerminal()){
            TokenType type = child->getChildren()[0]->getToken()->getType();
            
            list<TokenType>::const_iterator findIter = std::find(BinaryOperatorTokens.begin(), BinaryOperatorTokens.end(), type);
            if(findIter != BinaryOperatorTokens.end()){
                // found dyadic operator
                SyntaxTree* leftSideExprNode = exprNode->getChildren()[0];
                CodeExpression* leftSideExpr = genExpression(leftSideExprNode);
                
                opExpression = genBinaryExpression(leftSideExpr, child);
            }
        }
    }
    
    return opExpression;
};



SyntaxTree* ASTGenerator::findNextTerminalRec(SyntaxTree* parent, TokenType ignoreToken){
    
    vector<SyntaxTree*> children = parent->getChildren();
    for (int i=0; children.size() > i; i++) {
        SyntaxTree* child = children[i];
        if(child->isTerminal())
        {
            if(child->getToken()->getType() != ignoreToken){
                return child;
            }
        }
    }
    
    for (int i=0; children.size() > i; i++) {
        SyntaxTree* child = children[i];
        if(!child->isTerminal())
            return findNextTerminalRec(child, ignoreToken);
    }
    
    return NULL;
};

vector<SyntaxTree*> ASTGenerator::findCommandNodes(SyntaxTree* node){
    vector<SyntaxTree*> statementNodes;
    
    if(node->hasChildren()){
        
        vector<SyntaxTree*> childs = node->getChildren();
        
        for (int i=0; childs.size() > i; i++) {
            SyntaxTree* possibleCmd = childs[i];
            
            if(!possibleCmd->isTerminal()){
                if(possibleCmd->getNonTerminal()->getName() == "CMD"
                   || possibleCmd->getNonTerminal()->getName() == "REPCMD"){
                    
                    statementNodes.push_back(possibleCmd);
                    
                    vector<SyntaxTree*> subCmds = findCommandNodes(possibleCmd);
                    statementNodes.insert( statementNodes.end(), subCmds.begin(), subCmds.end() );
                }
            }
        }
        
    }
    

    return statementNodes;
};

vector<CodeStatement*> ASTGenerator::genCodeStatements(SyntaxTree* node){
    vector<CodeStatement*> statements;
    
    vector<SyntaxTree*> statementNodes = findCommandNodes(node);
    
    cout << "ASTGenerator: found " << statementNodes.size() << " Statements\n";
    
    for (int i=0; statementNodes.size() > i; i++) {
        CodeStatement* statement = genCodeStatement(statementNodes[i]);
        if(statement != NULL) statements.push_back(statement);
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

vector<SyntaxTree*> ASTGenerator::findAllNonTerminalRecExcluding(SyntaxTree* parent, const string& name,  set<string> excludeSet){
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
                    continue;
                }
                if(excludeSet.count(child->getNonTerminal()->getName()) == 0){
					vector<SyntaxTree*> subMatches = findAllNonTerminalRecExcluding(child, name, excludeSet);
					for(int j=0; subMatches.size() > j; j++){
						matches.push_back(subMatches[j]);
					}
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





CodeProgram* ASTGenerator::generate(){
    
    _program = new CodeProgram();
    _context = "__main__";
    // extract prog param list
    SyntaxTree* progParamList = findChildNonTerminal(_rootNode, "PROGPARAMLIST");
    if(progParamList != NULL)
    {
        vector<CodeParameter*> params = genCodeParameters(progParamList);
        
        cout << "found PROGPARAMLIST with " << params.size() << " params.\n";
        
        for (int i=0; params.size() > i; i++) {
            _program->addProgParam(params[i]);
        }
    }else{
        throw new GrammarException("Missing PROGPARAMLIST!");
    }
    
    // extract declarations
    SyntaxTree* gobalDecls = findChildNonTerminal(_rootNode, "OPTGLOBALCPSDECL");
    if(gobalDecls != NULL)
    {
        vector<CodeDeclaration*> params = genCodeDeclarations(gobalDecls);
        for (int i=0; params.size() > i; i++) {
            _program->addGlobalDecl(params[i]);
        }
    }else{
        throw new GrammarException("Missing OPTGLOBALCPSDECL!");
    }
        
    // extract Statements
    SyntaxTree* cmdNode = findChildNonTerminal(_rootNode, "CPSCMD");
    if(cmdNode != NULL)
    {
        vector<CodeStatement*> statements = genCodeStatements(cmdNode);
        for (int i=0; statements.size() > i; i++) {
            _program->addProgStatement(statements[i]);
        }
    }else{
          throw new GrammarException("Missing CPSCMD!");
    }
    
    return _program;
};