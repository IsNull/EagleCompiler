//
//  Scanner.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__Scanner__
#define __EagleCompiler__Scanner__

#include <iostream>
#include "TokenList.h"

using namespace std;

class Scanner {
    
public:
    const TokenList* scan(string source);
    
    
    
};


#endif /* defined(__EagleCompiler__Scanner__) */
