cmake_minimum_required(VERSION 3.20)
project(Dyno CXX)

file(GLOB_RECURSE cxx_sources CONFIGURE_DEPENDS "src/Dyno/*.cpp")

add_library(Dyno src/Dyno.h ${cxx_sources})

set_target_properties(Dyno PROPERTIES LINKER_LANGUAGE CXX)