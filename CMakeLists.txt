cmake_minimum_required(VERSION 3.8)

PROJECT(dmre)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

InterfaceImport("dmre" "include" "")

if (PROJECT_IS_TOP_LEVEL)

    ExeImport("test" "dmcli11")
endif(PROJECT_IS_TOP_LEVEL)

