cmake_minimum_required(VERSION 3.15)
project(CaseMaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

# Also collect headers so IDEs know they belong to the target
file(GLOB_RECURSE CASEMAKER_HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.hpp")

add_executable(CaseMaker main.cpp ${CASEMAKER_SOURCES} ${CASEMAKER_HEADERS})

# Simple include paths so headers in core/ and case/ are found
target_include_directories(CaseMaker PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/case
)
