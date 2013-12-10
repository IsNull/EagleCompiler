//
//  ScannerEnums.h
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#ifndef __EagleCompiler__ScannerEnums__
#define __EagleCompiler__ScannerEnums__

#include <iostream>

/**
 * Represents a basic state of the scanner
 * for diffrent grammar contexts
 */
enum class KnownScannerState {
    Default,                    // default context
    LineComment,                // the scanner is in a line comment context
    MultiLineComment,           // the scanner is in a multiline comment context
    LiteralString,              // the scanner is in literal string context
    LiteralStringExpression     // the scanner is in literal string expresion
};

std::ostream& operator<<(std::ostream& o, KnownScannerState t);

#endif /* defined(__EagleCompiler__ScannerEnums__) */