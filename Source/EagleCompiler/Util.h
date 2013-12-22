//
//  Util.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__Util__
#define __EagleCompiler__Util__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Util
{
public:
    static std::string subStrFromArr(char* buff, int start, int end);

    static bool isWhiteSpace(char c);
    
    static bool isNewLine(char c);
    
    static vector<string> split(const string& s, const string& delim, const bool keep_empty = true);
};

#endif /* defined(__EagleCompiler__Util__) */
