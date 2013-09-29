//
//  Util.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Util.h"
#include <string>

std::string Util::subStrFromArr(char* buff, int start, int end){
    end++;
    int len = end-start;
    char subbuff[len+1];
    memcpy( subbuff, &buff[start], len );
    subbuff[len] = '\0';
    return subbuff;
}


bool Util::isWhiteSpace(char c){
    static char whitespaceChars[] = {' ', '\t', '\n', '\r'};
    static int whitespaceCharsCnt = sizeof(whitespaceChars);
    
    for(int j=0; j<whitespaceCharsCnt; j++){
        if(c == whitespaceChars[j])
            return true;
    }
    return false;
}