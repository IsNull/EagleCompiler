//
//  Scanner.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include <cctype>

#include "Scanner.h"
#include "Token.h"
#include "TokenList.h"
#include "Util.h"

using namespace std;



int scanTest(int i){
    return i * 2;
}


Scanner::Scanner(){
    _state = ScannerState::Default;
    _tokens = new TokenList();
}


void Scanner::init(string source){
    // Init our char buffer from the string
    
    _sourceSize = (int)source.size();
    _sourceData = new char[_sourceSize+1];
    _sourceData[_sourceSize]=0;
    memcpy(_sourceData,source.c_str(),_sourceSize);
}

const TokenList* Scanner::scan(string source){
    
    init(source);
    
    int tokenStart = 0; // points to the start of the current Token
    int tokenEnd = 0;   // points to the end of the current Token
   
    
    _currentType = TokenType::None;
    
    while (true) {
        
        TokenType rollingToken;
        
        switch (_state) {
            case ScannerState::Default:
                
                rollingToken = isToken(tokenStart, tokenEnd);

                break;
                
            case ScannerState::MultiLineComment:
                //TODO
                rollingToken = TokenType::None;
                break;
                
            case ScannerState::LiteralString:
                // TODO
                rollingToken = TokenType::None;
                break;
                
            default:
                // exception No state handling
                rollingToken = TokenType::None;
                break;
        }
        
        // DEBUG ONLY - print rolling token stream
/*        cout <<  "(" << tokenStart << "," << tokenEnd << ") rolling token: "
        + TokenNames.find(rollingToken)->second + "\n"*/;
        cout <<  "(" << tokenStart << "," << tokenEnd << ") rolling token: "
        << rollingToken << "\n";
        
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

                    cout << "ERROR UNEXPECTED SIGN: '" + Util::subStrFromArr(_sourceData, tokenStart, tokenEnd) + "' (no Token matches)\n";
                    
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
    
    TokenType rangeTokenType = TokenType::None;
    
    
    string possibleToken = Util::subStrFromArr(_sourceData, start, end);
    
    // Depending on the current state we have diffrnet grammars
    // i.e. Default, LiteralString or Comment grammar...
    
    // for now, we handle only the default grammar:
    
    
    // ---- STATE: DEFAULT GRAMMAR ---- (TODO: Refactor into state pattern)
    
    // Check if current range is terminal/operator token
    // then check if range is identifier/literal number
    
    TokenMap::const_iterator it = TokenMap_Default.find(possibleToken);
    
    if(it != TokenMap_Default.end()){
        // found matching token
        rangeTokenType = it->second;
    }
        
    if(rangeTokenType == TokenType::None){
        // we could not find a matching token in our context map
        // we have to check for identifiers and literals by ourselfes:
        
        if(isNumber(start, end))
        {
            rangeTokenType = TokenType::LiteralNumber;
        }else if(isIdentifier(start, end)){
            rangeTokenType = TokenType::Identifier;
        }else if(isWhiteSpace(start, end)){
            rangeTokenType = TokenType::WhiteSpace;
        }
    }
    
    // ---- END STATE: DEFAULT GRAMMAR ----
    
    return rangeTokenType;
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
 * I.e. the range must only contain whitespace chars (space, tabs, newline etc.)
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

void Scanner::endToken(TokenType type, int start, int end){
    
    // Filter whitespaces if desired
    if(_omitWhiteSpaces && type == TokenType::WhiteSpace)
        return;
    
    // Extract the token string from the source data
    string tokenValue = Util::subStrFromArr(_sourceData, start, end);
    
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

