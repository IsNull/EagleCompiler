//
//  ParserModel.cpp
//  EagleCompiler
//
//  Created by Pascal Büttiker on 17/10/13.
//  Copyright (c) 2013 Pascal Büttiker. All rights reserved.
//

#include "ParserModel.h"



//
// ------------------- ProductionTable ---------------------
//


void ParserTable::AddProductionRule(ProductionRule& rule){

    _productionRules.insert(
                            map<NonTerminal, ProductionRule>::value_type(rule.getLeftSide(), rule)
                            );
}