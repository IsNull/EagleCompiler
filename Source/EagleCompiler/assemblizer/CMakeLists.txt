set(assemblizer_src 
	AssemblerInstruction.cpp
	Assemblizer.cpp
	NumericVariable.cpp
	StringVariable.cpp
	Variable.cpp)
	
add_library(assemblizer ${assemblizer_src})