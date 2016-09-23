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

# find boost
set(BOOST_ROOT "libs/boost_1_61_0")
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK OFF)

find_package (Boost)
if (Boost_FOUND)
	include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

# --------------- INCLUDING DIRS ---------------
include_directories(${PROJECT_SOURCE_DECLARATION_DIRECTORY})


# ---------------- LINKING LIBS ----------------
target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})


# --------------- INCLUDING EXECUTABLES ---------------
add_executable (${PROJECT_NAME} ${MAIN_FILE})
