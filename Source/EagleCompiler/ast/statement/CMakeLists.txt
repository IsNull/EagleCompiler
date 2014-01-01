set (statement_src
CodeStatement.cpp
CodeSkipStatement.cpp
CodeAssignmentStatement.cpp
CodeIfStatement.cpp
CodeWhileStatement.cpp
CodeProcedureCallStatement.cpp
CodeFunctionCallStatement.cpp
CodeInputStatement.cpp
CodeOutputStatment.cpp
)
add_library(statement OBJECT ${statement_src})
