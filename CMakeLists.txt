cmake_minimum_required(VERSION 3.28)

project(Mapgen LANGUAGES CXX)

###### add and load monorepo script ########
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
include(mono_repo)

load_all_components()
