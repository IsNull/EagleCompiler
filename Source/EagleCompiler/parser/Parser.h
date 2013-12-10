//
//  Util.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__Parser__
#define __EagleCompiler__Parser__

#include <iostream>
#include <string>
#include "../TokenList.h"
#include "../Token.h"

class Parser
{
private:
    TokenList tokenlist;
    void consume(TokenType expectedToken);
    
    
public:
    Parser(TokenList tokenlist);
    

    
};

#endif /* defined(__EagleCompiler__Parser__) */
