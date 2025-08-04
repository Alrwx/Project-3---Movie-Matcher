cmake_minimum_required(VERSION 3.30)
project(Project_3___Movie_Matcher)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_3___Movie_Matcher
    main.cpp
    movie.cpp
    movie.h
    parsing.cpp
    parsing.h
    testingFunction.cpp
    testingFunction.h
    CustomMap.cpp
    prepareInput.cpp
    Storage.cpp
    )
file(COPY ${CMAKE_SOURCE_DIR}/files DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/test DESTINATION ${CMAKE_BINARY_DIR})