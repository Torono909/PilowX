cmake_minimum_required(VERSION 3.20.2)

project(MCExternal)

# Why the fuck. KILL ME NOW. ARCH FUCK YOU WHATS WRONG WITH UR FUCKING HEADERS WHYYYYYYYYYyy
add_compile_options(-Wall -Wextra)
add_link_options(-lX11 -lXtst)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
