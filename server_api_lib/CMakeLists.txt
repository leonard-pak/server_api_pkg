cmake_minimum_required(VERSION  3.0.2)
project(server_api_lib)

add_library(${PROJECT_NAME} STATIC
  src/robotic-arm-ctrl.cpp
  src/two-wheel-robot-ctrl.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)
