//
//  Scanner.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include <cctype>

#include "Scanner.h"

using namespace std;



Scanner::Scanner(){
    _tokens = new TokenList();
     setContext(KnownScannerState::Default);
}

void Scanner::setContext(KnownScannerState stateType){
    
    // get current active state and remember it
    KnownScannerState prevState = KnownScannerState::Default;
    if(_contextState){
        prevState = _contextState->getState();
    }
    
    // TODO refactor this
    // find the impl. for the KnownScannerState
    IScannerContext *context;
    
    switch (stateType) {
        case KnownScannerState::Default:
            context = ScannerContextDefault::instance();
            break;
            
        case KnownScannerState::LineComment:
            context = ScannerContextLineComment::instance();
            break;
            
        case KnownScannerState::MultiLineComment:
            context = ScannerContextMultiLineComment::instance();
            break;
            
        case KnownScannerState::LiteralString:
            context = ScannerContextLiteralString::instance();
            break;
            
        case KnownScannerState::LiteralStringExpression:
            context = ScannerContextLiteralStringExpression::instance();
            break;
            
        default:
            // Default case always fall back to default state
            context = ScannerContextDefault::instance();
            cout << "ERROR: setContext -> unhandled context, switching back to Default.";
            break;
    }
    
    
    // set the new state as active
    _contextState = context;
    _contextState->startContext(this, prevState);
}

void Scanner::init(string source){
    // Init our char buffer from the string
    
    _sourceSize = (int)source.size();
    _sourceData = new char[_sourceSize+1];
    _sourceData[_sourceSize]=0;
    memcpy(_sourceData, source.c_str(), _sourceSize);
}


const TokenList* Scanner::scan(string source){
    
    init(source);
    
    int tokenStart = 0; // points to the start of the current Token
    int tokenEnd = 0;   // points to the end of the current Token
   
    
    _currentType = TokenType::None;
    
    while (true) {
        
        if(_contextState->nextState() != _contextState->getState()){
            cout << "\t>>>\t\tSwitching state to: " << _contextState->nextState() << " <<<\n";
            setContext(_contextState->nextState());
            cout << "\t>>>\t\tContext is now " << _contextState->getState() << " <<<\n";

        }
        
        
        TokenType rollingToken = isToken(tokenStart, tokenEnd);
        
        
        
#ifdef IS_DEBUG
        // DEBUG ONLY - print rolling token stream
        cout <<  "(" << tokenStart << "," << tokenEnd << ") rolling token: " << rollingToken << "\n";
#endif
        
        bool eof = tokenEnd == _sourceSize-1;
        
        if(!eof){
            if(rollingToken == TokenType::None){
                // the current range is no valid token
                if(_currentType != TokenType::None)
                {
                    endToken(_currentType, tokenStart, tokenEnd-1);
                    tokenStart = tokenEnd;
                    _currentType = TokenType::None;
                }else{

                    cout << "ERROR UNEXPECTED SIGN: '" + range(tokenStart, tokenEnd) + "' (no Token matches)\n";
                    
                    // ignore unknown tokes (alternatively, just throw an exception here... but thats lazy u know :) )
                    // just advance scan range +1
                    tokenStart++;
                    tokenEnd++;
                }
            }else{
                _currentType = rollingToken;
                tokenEnd++;
            }
        }else{
            cout << "EOF!\n"; // DEBUG ONLY
            handleEOF(rollingToken, tokenStart, tokenEnd);
            
            break; // We are done now
        }
        
    }
    
    Token* t = new Token(TokenType::Sentinel);
    _tokens->add(*t);
    
    return _tokens;
}

/**
 * Handle the EOF case, that is, ensure the current open token is closed
 * and in case it was a token span > 1 ensure the last sign is also handled.
 *
 *
 *
 * --A bit hacky--
 */
void Scanner::handleEOF(TokenType rollingToken, int tokenStart, int tokenEnd){
    if(rollingToken == TokenType::None){
        
        // EOF case 1
        
        // the current token range is NOT valid
        // that means the last char is not part of the previous token
        
        if(_currentType != TokenType::None){
            // the previous token was valid, end it
            endToken(_currentType, tokenStart, tokenEnd-1);
            tokenStart = tokenEnd;
        }
        
        // check last sign if appropriate token
        _currentType = isToken(tokenStart, tokenEnd);
        if(_currentType != TokenType::None){
            endToken(_currentType, tokenStart, tokenEnd);
        }
    }else{
        // EOF case 2
        
        // the current token range is valid
        endToken(rollingToken, tokenStart, tokenEnd);
    }
}


/**
 * Determines the token type of the given range (in the given context)*
 *
 * Returns a token type if the whole range has been identified as a token
 * or TokenType::None if the range is not a valid token
 *
 * TODO(*)
 */
TokenType Scanner::isToken(int start, int end){
    return _contextState->stepRange(start, end);
}

string Scanner::range(int start, int end){
    return Util::subStrFromArr(_sourceData, start, end);
}


bool Scanner::isNumber(int start, int end){
    
    char* cp = _sourceData + (sizeof(char) * start);
    int len = end-start+1;
    
    for (int i=0; i<len; i++) {
        if(!isdigit(*cp))
            return false;
        cp++;
    }
    
    return true;
}

/**
 * Checks if the given char range is a valid Identifier
 * 
 * Valid identiviers must start with an alpha and then continue with alpha-num.
 *
 * a
 * abc
 * a1
 *
 */
bool Scanner::isIdentifier(int start, int end){
    
    char* cp = _sourceData + (sizeof(char) * start);
    int len = end-start+1;
    
    for (int i=0; i<len; i++) {
        
        if(i==0 && !isalpha(*cp))
            return false;
        else if( i != 0 && !isalnum(*cp))
            return false;
        cp++;
    }
    
    return true;
}

/**
 * Checks if the given char range is a whitespace
 * I.e. the range must only contain whitespace chars (space, tabs etc.)
 *
 */
bool Scanner::isWhiteSpace(int start, int end){
    
    char* cp = _sourceData + (sizeof(char) * start);
    int len = end-start+1;

    for (int i=0; i<len; i++) {
        if(!Util::isWhiteSpace(*cp))
            return false;
        cp++;
    }
    
    return true;
}


/**
 * Checks if the given char range is a newline
 * I.e. the range must only contain newline chars
 *
 */
bool Scanner::isNewLine(int start, int end){
    
    char* cp = _sourceData + (sizeof(char) * start);
    int len = end-start+1;
    
    for (int i=0; i<len; i++) {
        if(!Util::isNewLine(*cp))
            return false;
        cp++;
    }
    
    return true;
}


void Scanner::endToken(TokenType type, int start, int end){
    
    // Filter whitespaces if desired
    if(_omitWhiteSpaces && type == TokenType::WhiteSpace)
        return;
    
    // Extract the token string from the source data
    string tokenValue = range(start, end);
    
    // check if token is keyword, and if so, inject specific keyword token
    if(type == TokenType::Identifier)
    {
        TokenType keyword = Token::findKeyword(tokenValue);
        if(keyword != TokenType::None)
            type = keyword;
    }
    
    Token* t = new Token(type, tokenValue);
    _tokens->add(*t);
}

