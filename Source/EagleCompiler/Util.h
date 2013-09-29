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

class Util
{
public:
    static std::string subStrFromArr(char* buff, int start, int end);

    static bool isWhiteSpace(char c);
};

#endif /* defined(__EagleCompiler__Util__) */
