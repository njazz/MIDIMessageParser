cmake_minimum_required(VERSION 2.8.12)
project(py_abs_mm_core)
enable_language(CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -funroll-loops -fomit-frame-pointer")

add_subdirectory(pybind11)

set(CMAKE_C_FLAGS "-std=gnu99 -funroll-loops -fomit-frame-pointer")

set(SOURCE_FILES
	# ../src/MIDIParser.c
)

# set_source_files_properties(../src/MIDIParser.c PROPERTIES LANGUAGE CXX)

# add_library(midiparser STATIC ../src/MIDIParser.c)

INCLUDE_DIRECTORIES(../src)

pybind11_add_module(py_midiparser ${SOURCE_FILES} py_midiparser.cpp)

# target_link_libraries(py_midiparser midiparser)
