cmake_minimum_required(VERSION 3.16)

# set the project name
project(SequencedSet)

configure_file(SequencedSetProject.h.in SequencedSetProject.h)
target_include_directories(SequencedSet PUBLIC
                           "$SequencedSet"
                           )

# add the executable
add_executable(SequencedSet testDriver.cxx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)