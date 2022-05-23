cmake_minimum_required(VERSION 3.16)

project(digital_twin
  VERSION 0.1
  DESCRIPTION "Digital Twin Program"
  LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++2a")

include(CheckLanguage)
check_language(CUDA)
if (CMAKE_CUDA_COMPILER)
  enable_language(CUDA)
else()
  message(STATUS "No cuda compiler detected.")
endif()

set(CMAKE_PREFIX_PATH "$ENV{HOME}/opt/libtorch")
find_package(Torch REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(fmt REQUIRED)
find_package(Freetype REQUIRED)

add_executable(digital_twin
  src/main.cpp
  src/render_system.cpp
  src/input_system.cpp
  src/affine_frame.cpp
  src/bag_loader.cpp
  src/point_cloud.cpp
  src/quaternion.cpp
  )
target_include_directories(digital_twin PUBLIC
  ${FREETYPE_INCLUDE_DIRS}
  ${FMT_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
  ${GLEW_INCLUDE_DIRS}
  /opt/ros/noetic/include
)
target_link_directories(digital_twin PUBLIC
  /usr/local/lib64
  /opt/ros/noetic/lib
  )
target_link_libraries(digital_twin
  stdc++fs
  fmt::fmt
  roscpp
  rosbag
  rosbag_storage
  rostime
  ${TORCH_LIBRARIES}
  ${FREETYPE_LIBRARIES}
  ${ASSIMP_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${GLEW_LIBRARIES}
)
