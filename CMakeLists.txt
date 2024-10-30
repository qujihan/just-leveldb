cmake_minimum_required(VERSION 3.21)

project(just-leveldb
    VERSION 0.0.1
    DESCRIPTION "read leveldb source code"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 输出文件为 data 目录
set(LEVELDB_DATA_DIR "data")

# leveldb lib
set(LEVELDB_BUILD_TESTS ON CACHE INTERNAL "")
set(LEVELDB_BUILD_BENCHMARKS ON CACHE INTERNAL "")
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "")
add_subdirectory(leveldb)
include_directories(leveldb/include)

set(LEVELDB_DATA_DIR_PATH ${PROJECT_SOURCE_DIR}/${LEVELDB_DATA_DIR}/)
configure_file(${PROJECT_SOURCE_DIR}/src/include/config.h.in ${PROJECT_SOURCE_DIR}/src/include/config.h)

# append libs 
list(APPEND EXTERNAL_LIBS leveldb)

# src
function(create_executable_file TARGET_NAME)
    add_executable(${TARGET_NAME} src/${TARGET_NAME}.cc)
    target_link_libraries(${TARGET_NAME} PUBLIC ${EXTERNAL_LIBS})
    target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src/include)
endfunction()

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)
foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(SRC_NAME ${SRC_FILE} NAME_WE)
    create_executable_file(${SRC_NAME})
endforeach()