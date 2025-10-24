cmake_minimum_required(VERSION 3.28)

project(Mapgen-App)

import(Mapgen-Core)

add_executable(${PROJECT_NAME} "Source/Mapgen-App/main.cpp")
target_link_libraries(${PROJECT_NAME} Mapgen-Core)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
