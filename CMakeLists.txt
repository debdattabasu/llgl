cmake_minimum_required (VERSION 2.8) 
project(Llgl)
set(CMAKE_MODULE_PATH ${Llgl_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})
#add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Llgl_BINARY_DIR})

if(NOT MSVC_IDE)
	include(Cotire)
endif()

option(LLGL_STATIC "Build Llgl statically" OFF)

if(LLGL_STATIC)
	set(LLGL_LIBRARY_TYPE STATIC)
	add_definitions(-DLLGL_STATIC)
else()
	set(LLGL_LIBRARY_TYPE SHARED)
endif()

add_subdirectory(Llgl)
add_subdirectory(LlglDriverDirect3D11)
add_subdirectory(LlglExamples)