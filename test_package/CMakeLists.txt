cmake_minimum_required(VERSION 3.20)
project(DynoTest CXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)

find_package(Catch2 REQUIRED)
find_package(Dyno REQUIRED)

find_program(GCOV_PATH gcovr)
link_libraries(gcov)

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage -g3")

enable_testing()

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp")

MESSAGE("ALERT")
MESSAGE("${SRC}")

foreach( SRC ${SOURCES} )
    get_filename_component(FNAME ${SRC} NAME_WE)
    string(CONCAT TARGET "Dyno_test_" ${FNAME})
    string(CONCAT TNAME "Dyno: " ${FNAME})
    add_executable( ${TARGET} ${SRC} )
    target_link_libraries( ${TARGET} Catch2::Catch2WithMain )
    target_link_libraries( ${TARGET} dyno::dyno )
    add_test(NAME ${TNAME} COMMAND ${TARGET})
endforeach( SRC ${SOURCES} )

file(GLOB_RECURSE cxx_sources CONFIGURE_DEPENDS "${DYNO_PATH}/*.cpp")

make_directory(${ROOT_DIR}/coverage)
add_custom_target(Dyno_cov
    ${GCOV_PATH} ${PROJECT_BINARY_DIR}/CMakeFiles/*.dir/src -r ${DYNO_PATH}/include  --html-details -o ${ROOT_DIR}/coverage/index.html -s --exclude-unreachable-branches --exclude-throw-branches
)