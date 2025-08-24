cmake_minimum_required(VERSION 3.15)  # 3.15+ recommended for modern features

# Project definition
project(HTTP-1.1 
    VERSION 1.0.0
    DESCRIPTION "Minimal HTTP/1.1 Server"
    LANGUAGES CXX
)

# ================================
# Global Settings
# ================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # No compiler-specific extensions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build types
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Release, Debug, RelWithDebInfo, MinSizeRel" FORCE)
endif()

# ================================
# Sources & Executable
# ================================
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/server.cpp
)

add_executable(HttpServer ${SOURCES})
target_include_directories(HttpServer PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ================================
# Security & Warning Flags
# ================================
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(HttpServer PRIVATE 
        -Wall -Wextra -Wpedantic       # Strict warnings
        -Werror                        # Treat warnings as errors
        -Wconversion -Wsign-conversion # Catch narrowing/signedness issues
        -Wshadow                       # Shadowed variables
        -Wnull-dereference             # Null ptr detection
        -fstack-protector-strong       # Stack protection
        -fPIE -fPIC                     # Position independent (security)
        $<$<CONFIG:Release>:-O2>       # Optimize Release builds
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(HttpServer PRIVATE 
        /W4 /WX            # Strict warnings, treat as error
        /permissive-       # Standards compliance
        /guard:cf          # Control Flow Guard
        /GS                # Buffer security checks
    )
endif()

# ================================
# Static Analysis (Optional)
# ================================
# Enable clang-tidy if available
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set_target_properties(HttpServer PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

# Enable cppcheck if available
find_program(CPPCHECK_EXE NAMES "cppcheck")
if(CPPCHECK_EXE)
    message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE};--enable=all;--inconclusive;--quiet")
endif()

# ================================
# Testing Support
# ================================
option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests) # put your tests in /tests folder
endif()

# ================================
# Install/Export Rules
# ================================
install(TARGETS HttpServer
    RUNTIME DESTINATION bin
)

# ================================
# Packaging (optional for deploy)
# ================================
include(CPack)
