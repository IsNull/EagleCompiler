//
//  ScannerEnums.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 9/29/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "ScannerEnums.h"

using namespace std;

ostream& operator<<(ostream& o, KnownScannerState t){
    switch (t) {
        case KnownScannerState::Default:
            o << "Default";
            break;
            
        case KnownScannerState::LineComment:
            o << "LineComment";
            break;
            
        case KnownScannerState::MultiLineComment:
            o << "MultiLineComment";
            break;
            
        case KnownScannerState::LiteralString:
            o << "LiteralString";
            break;
            
        default:
            o << "<unknown KnownScannerState>";
            break;
            }
            
            return o;
    };