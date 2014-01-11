#include "statement/CodeSkipStatement.h"
#include "statement/CodeIfStatement.h"
#include "statement/CodeStatement.h"
#include "statement/CodeProcedureCallStatement.h"
#include "statement/CodeInputStatement.h"
#include "statement/CodeOutputStatment.h"
#include "statement/CodeFunctionCallStatement.h"
#include "statement/CodeAssignmentStatement.h"
#include "statement/CodeWhileStatement.h"
#include "CodeObject.h"
#include "CodeGlobalImport.h"
#include "CodeParameter.h"
#include "CodeProgram.h"
#include "CodeGlobalInit.h"
#include "declaration/CodeFunctionDeclaration.h"
#include "declaration/CodeDeclaration.h"
#include "declaration/CodeProcedureDeclaration.h"
#include "declaration/CodeStorageDeclaration.h"
#include "type/CodeType.h"
#include "expression/CodeBinaryExpression.h"
#include "expression/CodeExpressionFunctionCall.h"
#include "expression/CodeExpression.h"
#include "expression/CodeExpressionInitializeVariable.h"
#include "expression/CodeExpressionLiteral.h"
#include "expression/CodeExpressionUnaryExpression.h"
#include "expression/CodeExpressionVariable.h"
#include "identifier/CodeIdentifier.h"
#include "identifier/CodeFunction.h"
#include "identifier/CodeVariable.h"
#include "identifier/CodeProcedure.h"
