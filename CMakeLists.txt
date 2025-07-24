cmake_minimum_required(VERSION 3.10)

project(HTTP-1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp 
    src/parser.cpp  
    src/server.cpp  
)

add_executable(HttpServer ${SOURCES})