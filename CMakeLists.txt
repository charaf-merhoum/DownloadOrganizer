cmake_minimum_required(VERSION 3.20)

project(DownloadOrganizer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} 
src/main.cpp

src/Core/ConfigParser.cpp
src/Core/FileOrganizer.cpp

src/Utils/StringUtils.cpp
)

if(MSVC)
	add_compile_options(/utf-8)
	else()
	add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
	endif()