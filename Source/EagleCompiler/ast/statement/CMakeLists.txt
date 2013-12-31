set (statement_src
CodeStatement.cpp
CodeAssignmentStatement.cpp
CodeIfStatement.cpp
CodeWhileStatement.cpp
CodeCallStatement.cpp
CodeInputStatement.cpp
CodeOutputStatment.cpp
)
add_library(statement OBJECT ${statement_src})
