set(parser_src 
	Parser.cpp
	ParseTableReader.cpp
	ASTGenerator.cpp)
	
add_library(parser ${parser_src})