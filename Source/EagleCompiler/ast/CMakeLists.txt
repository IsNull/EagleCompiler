add_subdirectory(declaration)
add_subdirectory(expression)
add_subdirectory(identifier)
add_subdirectory(statement)
add_subdirectory(type)


set (ast_src
CodeObject.cpp
CodeProgram.cpp
CodeGlobalInit.cpp
CodeGlobalImport.cpp
CodeParameter.cpp
)
add_library(ast ${ast_src} 
	$<TARGET_OBJECTS:declaration> 
	$<TARGET_OBJECTS:expression> 
	$<TARGET_OBJECTS:identifier> 
	$<TARGET_OBJECTS:statement> 
	$<TARGET_OBJECTS:type>
)
