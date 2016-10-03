## --------------------------------------------------------
## cmake file for the 'pmt' project.
##
## @author: Vinicius Carneiro <vcps@cin.ufpe.br>
## --------------------------------------------------------

# --------------- PROJECT ---------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set (PROJECT_NAME "pmt" CXX)
project(${PROJECT_NAME})


# --------------- SETTING VARS ---------------
# dirs
set(PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(MAIN_FILE ${PROJECT_SOURCE_DEFINITION_DIRECTORY}/main.cpp)
# flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# --------------- INCLUDING DIRS ---------------
include_directories(${PROJECT_SOURCE_DECLARATION_DIRECTORY})
include_directories("libs")


# --------------- INCLUDING EXECUTABLES ---------------
add_executable (${PROJECT_NAME} ${MAIN_FILE})
