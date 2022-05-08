cmake_minimum_required(VERSION 3.16)
project(sdl2-template)

set(CMAKE_C_STANDARD            99)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

if (APPLE)
    include_directories(/usr/local/include)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
	sdl2-template.cpp
)

target_link_libraries(
	${PROJECT_NAME}
)

if (APPLE)
	find_package(OpenGL REQUIRED)
endif()

if (!APPLE)
	find_library(OPENGL_LIB NAMES GL)
	target_link_libraries(${PROJECT_NAME} PRIVATE GL)
endif()

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)
