cmake_minimum_required(VERSION 3.28)

project(Mapgen-Lib)

add_library(
    ${PROJECT_NAME} STATIC
    "Source/Mapgen-Lib/Lib.cpp"
    "Source/Mapgen-Lib/Generators/Naive.cpp"
    "Source/Mapgen-Lib/IO.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
