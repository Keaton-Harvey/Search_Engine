cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
include(CTest)
set(CMAKE_VERBOSE_MAKEFILE ON) 
add_compile_options(-Wall -Wextra -pedantic)

add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp DocumentParser.cpp DocumentParser.h IndexHandler.cpp IndexHandler.h SearchEngine.cpp SearchEngine.h porter2_stemmer.h porter2_stemmer.cpp QueryProcessor.h QueryProcessor.cpp UserInterface.h UserInterface.cpp)
add_executable(test_AvlTreeMap test_AvlTreeMap.cpp)
add_test(NAME TestAvlTreeMap COMMAND test_AvlTreeMap)
add_executable(test_Persistence test_Persistence.cpp AvlTreeMap.h IndexHandler.h IndexHandler.cpp DocumentParser.h DocumentParser.cpp porter2_stemmer.h porter2_stemmer.cpp)
add_test(NAME TestPersistence COMMAND test_Persistence)

# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
