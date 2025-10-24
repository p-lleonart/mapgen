cmake_minimum_required(VERSION 3.28)

project(Mapgen-Core)

import(Mapgen-Lib)

add_library(
    ${PROJECT_NAME} STATIC
    "Source/Mapgen-Core/Core.cpp"
)
target_link_libraries(${PROJECT_NAME} Mapgen-Lib)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
