cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")


project(memory_pool)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} pthread)
