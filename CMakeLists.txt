cmake_minimum_required(VERSION 3.10)

project(HTTP-1.1 LANGUAGES CXX)

find_package(OpenSSL REQUIRED)
find_package(cpr REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp 
    src/parser.cpp  
    src/request.cpp  
    src/response.cpp  
    src/server.cpp  
)

add_executable(HttpServer ${SOURCES})
target_link_libraries(HttpServer PRIVATE cpr::cpr)