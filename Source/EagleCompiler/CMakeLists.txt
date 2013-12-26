add_subdirectory(scanner)
add_subdirectory(parser)
add_subdirectory(assemblizer)

set(token_src Token.cpp TokenList.cpp)
set(util_src Util.cpp)

add_executable(EagleCompiler main.cpp ${token_src} ${util_src} ${headers})

target_link_libraries(EagleCompiler scanner parser assemblizer)