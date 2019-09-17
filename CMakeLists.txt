cmake_minimum_required(VERSION 3.14)

project(plastic_linker)
# -Wno-dev flag to supress llvm dev errors
add_compile_options(-g -Wall -Wno-dev)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_executable(pl
    src/Main.cpp
    src/InputFile.cpp
    src/Memory.cpp)

target_include_directories(pl
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(pl
    PUBLIC cxx_std_17)

llvm_map_components_to_libnames(llvm_libs support core object)
target_link_libraries(pl ${llvm_libs})


