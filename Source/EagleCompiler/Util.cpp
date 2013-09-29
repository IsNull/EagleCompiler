//
//  Util.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "Util.h"
#include <string>

std::string subStrFromArr(char* buff, int start, int end){
    int len = end-start;
    char subbuff[len+1];
    memcpy( subbuff, &buff[start], len );
    subbuff[len] = '\0';
    return subbuff;
}