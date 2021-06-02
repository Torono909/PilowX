cmake_minimum_required(VERSION 3.20.2)

project(MCExternal)

add_compile_options(-Wall -Wextra -O2)
add_link_options(-lX11 -lXtst -lncurses)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
