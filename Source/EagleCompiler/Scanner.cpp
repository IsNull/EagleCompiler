//
//  Scanner.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Scanner.h"
#include "Token.h"
#include "TokenList.h"
#include "Util.h"
#include <cctype>

using namespace std;


Scanner::Scanner(){
    _state = ScannerState::Default;
    _tokens = new TokenList();
    
    
}



const TokenList* Scanner::scan(string source){
    
    // convert string to char array
    _sourceSize = (int)source.size();
    _sourceData = new char[_sourceSize+1];
    _sourceData[_sourceSize]=0;
    memcpy(_sourceData,source.c_str(),_sourceSize);
    
    int tokenStart = 0; // points to the start of the current Token
    int tokenEnd = 0;   // points to the end of the current Token
   
    
    _currentType = TokenType::None;
    
    
    while (true) {
        
        TokenType rollingToken;
        
        switch (_state) {
            case ScannerState::Default:
                
                rollingToken = isToken(tokenStart, tokenEnd);
                
                // DEBUG ONLY - print rolling token stream
                cout <<  "(" << tokenStart << "," << tokenEnd << ") rolling token: " + TokenNames.find(rollingToken)->second + "\n";
                
                
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
        
        bool eof = tokenEnd == _sourceSize-1;
        if(eof) cout << "EOF!\n"; // DEBUG ONLY
        
        if(!eof){
            if(rollingToken == TokenType::None){
                // the current range is no valid token
                if(_currentType != TokenType::None)
                {
                    endToken(_currentType, tokenStart, tokenEnd-1);
                    tokenStart = tokenEnd;
                    _currentType = TokenType::None;
                }else{
                    // ignore tokes, i.e. whitespaces
                    // advance scan range +1
                    tokenStart++;
                    tokenEnd++;
                }
            }else{
                _currentType = rollingToken;
                tokenEnd++;
            }
        }else{
            // EOF
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
            

            break;
        }
        
    }
    
    
    return _tokens;
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
    
    
    string possibleToken = subStrFromArr(_sourceData, start, end);
    
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
 * Checks if the given char range is an valid Identifier
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

void Scanner::endToken(TokenType type, int start, int end){
    string tokenValue = subStrFromArr(_sourceData, start, end);
    Token* t = new Token(type, tokenValue);
    _tokens->add(*t);
}

