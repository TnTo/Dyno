cmake_minimum_required(VERSION 3.20)
project(DynoTest CXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)

find_package(Catch2 REQUIRED)
find_package(Dyno REQUIRED)

find_program(GCOV_PATH gcovr)
link_libraries(gcov)

file(GLOB_RECURSE cxx_sources CONFIGURE_DEPENDS "${DYNO_PATH}/*.cpp")

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage -g3")

add_executable(Dyno_test_exe src/test.cpp ${cxx_sources})
target_link_libraries(Dyno_test_exe Catch2::Catch2WithMain)
target_link_libraries(Dyno_test_exe Dyno::Dyno)

make_directory(${ROOT_DIR}/coverage)
add_custom_target(Dyno_cov
    ${GCOV_PATH} ${PROJECT_BINARY_DIR}/CMakeFiles/Dyno_test_exe.dir/src -r ${DYNO_PATH}/include  --html-details -o ${ROOT_DIR}/coverage/index.html -s --exclude-unreachable-branches --exclude-throw-branches
    DEPENDS Dyno_test)

add_custom_target(Dyno_test Dyno_test_exe DEPENDS Dyno_test_exe)

add_custom_target(test DEPENDS Dyno_test Dyno_cov)