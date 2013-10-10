//
//  Token.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/28/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Token.h"

using namespace std;


ostream& operator<<(ostream& o, TokenType t) {
	
    map<TokenType, string>::const_iterator it = TokenNames.find(t);
    
    if(TokenNames.end() != it){
        // found it
        o << it->second;
    }else{
        // no mapping for tokentype t
        o << "<missing " << (int)t << ">";
    }
    
	return o;
}


