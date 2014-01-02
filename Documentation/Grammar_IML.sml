datatype term
  = LPAREN
  | RPAREN
  | COMMA
  | SEMICOLON
  | COLON
  | DEBUGIN
  | DEBUGOUT
  | BECOMES
  | DO
  | ENDPROGRAM
  | ENDFUN
  | ENDPROC
  | ENDIF
  | ENDWHILE
  | MULTOPR
  | ADDOPR
  | RELOPR
  | ATOMTYPE
  | CALL
  | BOOLOPR
  | CHANGEMODE
  | MECHMODE
  | ELSE
  | LITERAL
  | FUN
  | GLOBAL
  | IF
  | FLOWMODE
  | INIT
  | LOCAL
  | NOT
  | PROC
  | PROGRAM
  | RETURNS
  | SKIP
  | WHILE
  | IDENT
  | STRCONCATOPR
  | THEN

val string_of_term =
  fn LPAREN  => "LPAREN"
   | RPAREN   => "RPAREN"
   | COMMA  => "COMMA"
   | SEMICOLON => "SEMICOLON"
   | COLON  => "COLON"
   | DEBUGIN => "DEBUGIN"
   | DEBUGOUT => "DEBUGOUT"
   | BECOMES => "BECOMES"
   | DO => "DO"
   | ENDPROGRAM => "ENDPROGRAM"
   | ENDFUN => "ENDFUN"
   | ENDPROC => "ENDPROC"
   | ENDIF => "ENDIF"
   | ENDWHILE => "ENDWHILE"
   | MULTOPR => "MULTOPR"
   | ADDOPR => "ADDOPR"
   | RELOPR => "RELOPR"
   | ATOMTYPE => "ATOMTYPE"
   | CALL => "CALL"
   | BOOLOPR => "BOOLOPR"
   | CHANGEMODE => "CHANGEMODE"
   | MECHMODE => "MECHMODE"
   | ELSE => "ELSE"
   | LITERAL => "LITERAL"
   | FUN => "FUN"
   | GLOBAL => "GLOBAL"
   | IF => "IF"
   | FLOWMODE => "FLOWMODE"
   | INIT => "INIT"
   | LOCAL => "LOCAL"
   | NOT => "NOT"
   | PROC => "PROC"
   | PROGRAM => "PROGRAM"
   | RETURNS => "RETURNS"
   | SKIP => "SKIP"
   | WHILE => "WHILE"
   | IDENT => "IDENT"
   | STRCONCATOPR => "STRCONCATOPR"
   | THEN => "THEN"

datatype nonterm
  = program
  | optGlobalCpsDecl
  | progParamList
  | optProgParamCps
  | progParamCps
  | repProgParam
  | progParam
  | typedIdent
  | cpsDecl
  | repDecl
  | cpsCmd
  | decl
  | stoDecl
  | cpsStoDecl
  | repStoDecl
  | funDecl
  | optGlobImpList
  | optCpsStoDecl
  | procDecl
  | paramList
  | optParam
  | repParam
  | globImplList
  | repGlobImp
  | param
  | optFlowMode
  | optMechMode
  | globImp
  | optChangeMode
  | cmd
  | optGlobInitList
  | repCmd
  | expr
  | strTerm
  | exprList
  | globInitList
  | repIdent
  | term1
  | repBoolOprTerm1
  | repConcOprExpr
  | term2
  | optRelOprTerm2
  | term3
  | repAddOprTerm3
  | factor
  | optFactorIdent
  | optArrFactor
  | repMultOprFactor
  | optExpr
  | repExpr
  | monadicOpr
  | identFactor

val string_of_nonterm =
  fn program => "program"
   | optGlobalCpsDecl => "optGlobalCpsDecl"
   | progParamList => "progParamList"
   | optProgParamCps => "optProgParamCps"
   | progParamCps => "progParamCps"
   | repProgParam => "repProgParam"
   | progParam => "progParam"
   | typedIdent => "typedIdent"
   | cpsDecl => "cpsDecl"
   | repDecl => "repDecl"
   | cpsCmd => "cpsCmd"
   | decl => "decl"
   | stoDecl => "stoDecl"
   | cpsStoDecl => "cpsStoDecl"
   | repStoDecl => "repStoDecl"
   | funDecl => "funDecl"
   | optGlobImpList => "optGlobImpList"
   | optCpsStoDecl => "optCpsStoDecl"
   | procDecl => "procDecl"
   | paramList => "paramList"
   | optParam => "optParam"
   | repParam => "repParam"
   | globImplList => "globImplList"
   | repGlobImp => "repGlobImp"
   | param => "param"
   | optFlowMode => "optFlowMode"
   | optMechMode => "optMechMode"
   | globImp => "globImp"
   | optChangeMode => "optChangeMode"
   | cmd => "cmd"
   | optGlobInitList => "optGlobInitList"
   | repCmd => "repCmd"
   | expr => "expr"
   | strTerm => "strTerm"
   | exprList => "exprList"
   | globInitList => "globInitList"
   | repIdent => "repIdent"
   | term1 => "term1"
   | repBoolOprTerm1 => "repBoolOprTerm1"
   | repConcOprExpr => "repConcOprExpr"
   | term2 => "term2"
   | optRelOprTerm2 => "optRelOprTerm2"
   | term3 => "term3"
   | repAddOprTerm3 => "repAddOprTerm3"
   | factor => "factor"
   | optFactorIdent => "optFactorIdent"
   | optArrFactor => "optArrFactor"
   | repMultOprFactor => "repMultOprFactor"
   | optExpr => "optExpr"
   | repExpr => "repExpr"
   | monadicOpr => "monadicOpr"
   | identFactor => "identFactor"

val string_of_gramsym = (string_of_term, string_of_nonterm)

local
  open FixFoxi.FixFoxiCore
in

val productions =
[
(program,
    [[T PROGRAM, T IDENT, N progParamList, N optGlobalCpsDecl,T DO, N cpsCmd, T ENDPROGRAM]]),
(optGlobalCpsDecl,
    [[T GLOBAL, N cpsDecl],
    []]),
(progParamList,
	[[T LPAREN, N optProgParamCps, T RPAREN]]),
(optProgParamCps,
	[[N progParamCps],
	[]]),
(progParamCps,
	[[N progParam, N repProgParam]]),
(repProgParam,
	[[T COMMA, N progParam, N repProgParam],
	[]]),
(progParam,
	[[N optFlowMode, N optChangeMode, N typedIdent]]),
(typedIdent,
	[[T IDENT, T COLON, T ATOMTYPE]]),
(decl,
    [[N stoDecl],
    [N funDecl],
    [N procDecl]]),
(stoDecl,
    [[N optChangeMode, N typedIdent]]),
(funDecl,
    [[T FUN, T IDENT, N paramList, T RETURNS, N stoDecl, N optGlobImpList, N optCpsStoDecl, T DO, N cpsCmd, T ENDFUN]]),
(optGlobImpList,
    [[T GLOBAL, N globImplList],
    []]),
(optCpsStoDecl,
    [[T LOCAL, N cpsStoDecl],
    []]),
(procDecl,
    [[T PROC, T IDENT, N paramList, N optGlobImpList, N optCpsStoDecl, T DO, N cpsCmd, T ENDPROC]]),
(cpsDecl,
    [[N decl, N repDecl]]),
(repDecl,
    [[T SEMICOLON, N decl, N repDecl],
    []]),
(cpsStoDecl,
    [[N stoDecl, N repStoDecl]]),
(repStoDecl,
    [[T SEMICOLON, N stoDecl, N repStoDecl],
    []]),
(paramList,
    [[T LPAREN, N optParam, T RPAREN]]),
(optParam,
    [[N param, N repParam],
    []]),
(repParam,
    [[T COMMA, N param, N repParam],
    []]),
(param,
    [[N optFlowMode, N optMechMode, N optChangeMode, N typedIdent]]),
(optFlowMode,
    [[T FLOWMODE],
    []]),
(optMechMode,
    [[T MECHMODE],
    []]),
(globImplList,
    [[N globImp, N repGlobImp]]),
(repGlobImp,
    [[T COMMA, N globImp, N repGlobImp],
    []]),
(globImp,
    [[N optFlowMode, N optChangeMode, T IDENT]]),
(optChangeMode,
    [[T CHANGEMODE],
    []]),
(cmd,
    [[T SKIP],
    [N expr, T BECOMES, N expr],
    [T IF, N expr, T THEN, N cpsCmd, T ELSE, N cpsCmd, T ENDIF],
    [T WHILE, N expr, T DO , N cpsCmd, T ENDWHILE],
    [T CALL, T IDENT, N exprList, N optGlobInitList],
    [T DEBUGIN, N expr],
    [T DEBUGOUT, N expr]]),
(optGlobInitList,
    [[T INIT, N globInitList],
    []]),
(cpsCmd,
    [[N cmd, N repCmd]]),
(repCmd,
    [[T SEMICOLON, N cmd, N repCmd],
    []]),
(globInitList,
    [[T IDENT, N repIdent]]),
(repIdent,
    [[T COMMA, T IDENT, N repIdent],
    []]),
(expr,
    [[N strTerm, N repConcOprExpr]]),
(repConcOprExpr,
    [[T STRCONCATOPR, N strTerm, N repConcOprExpr],
    []]),
(strTerm,
    [[N term1, N repBoolOprTerm1]]),
(repBoolOprTerm1,
    [[T BOOLOPR, N term1, N repBoolOprTerm1],
    []]),
(term1,
    [[N term2, N optRelOprTerm2]]),
(optRelOprTerm2,
    [[T RELOPR, N term2],
    []]),
(term2,
    [[N term3, N repAddOprTerm3]]),
(repAddOprTerm3,
    [[T ADDOPR, N term3, N repAddOprTerm3],
    []]),
(term3,
    [[N factor, N repMultOprFactor]]),
(repMultOprFactor,
    [[T MULTOPR, N factor, N repMultOprFactor],
    []]),
(factor,
    [[T LITERAL],
    [T IDENT, N identFactor],
    [N monadicOpr, N factor],
    [T LPAREN, N expr, T RPAREN]]),
(identFactor,
	[[T INIT],
	[N exprList],
	[]]),
(exprList,
    [[T LPAREN, N optExpr, T RPAREN]]),
(optExpr,
    [[N expr, N repExpr],
    []]),
(repExpr,
    [[T COMMA, N expr, N repExpr],
    []]),
(monadicOpr,
    [[T NOT],
    [T ADDOPR]])
]

val S = program

val result = fix_foxi productions S string_of_gramsym

end (* local *)