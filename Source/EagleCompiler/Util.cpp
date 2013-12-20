//
//  Util.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Util.h"
#include <string>
#include <string.h>

std::string Util::subStrFromArr(char* buff, int start, int end){
    end++;
    int len = end-start;
    char subbuff[len+1];
    memcpy( subbuff, &buff[start], len );
    subbuff[len] = '\0';
    return subbuff;
}


bool Util::isWhiteSpace(char c){
    static char whitespaceChars[] = {' ', '\t'};
    static int whitespaceCharsCnt = sizeof(whitespaceChars);
    
    for(int j=0; j<whitespaceCharsCnt; j++){
        if(c == whitespaceChars[j])
            return true;
    }
    return false;
}

bool Util::isNewLine(char c){
    static char whitespaceChars[] = {'\n', '\r'};
    static int whitespaceCharsCnt = sizeof(whitespaceChars);
    
    for(int j=0; j<whitespaceCharsCnt; j++){
        if(c == whitespaceChars[j])
            return true;
    }
    return false;
}

/**
 * Split the given string by the given delemiter into a string-vector
 */
vector<string> Util::split(const string& s, const string& delim, const bool keep_empty) {
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}
