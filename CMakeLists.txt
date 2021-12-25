cmake_minimum_required(VERSION 3.13)
project(Pogl)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(LIBRARIES Boost::program_options glfw OpenGL::GL GLEW::GLEW ${CMAKE_DL_LIBS})

# Compilation Flags
####
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3 -fsanitize=address")

set(LINKER_FLAGS "")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LINKER_FLAGS ${LINKER_FLAGS} -fsanitize=address)
endif()

# Source files
####
set(MISC
    src/misc/image.cc
    src/misc/matrix4.cc
)

set(PARSER
    src/parser/obj_parser.cc
    src/parser/option_parser.cc
    src/parser/tga_parser.cc
)

set(SCENE
    src/scene/scene.cc
    src/scene/scene_builder.cc
)

set(UTILS
    src/utils/camera.cc
    src/utils/object.cc
    src/utils/program.cc
    src/utils/texture.cc
    src/utils/vao.cc
    src/utils/vbo.cc
    src/utils/window.cc
)

set(SRC
    src/main.cc
    ${MISC}
    ${PARSER}
    ${SCENE}
    ${UTILS}
)

# Include directory
include_directories(src/)

# Executable
####
set(EXECUTABLE_NAME pogl)

add_executable(${EXECUTABLE_NAME} ${SRC})
target_sources(${EXECUTABLE_NAME} PRIVATE ${SRC})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES} ${LINKER_FLAGS})
