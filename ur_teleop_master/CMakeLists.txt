cmake_minimum_required(VERSION 2.8.3)
project(ur_teleop_master)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/../auxiliary/cmake_modules")
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED roscpp tf)
find_package(Eigen3 REQUIRED)
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

set(OMEGA6_LIBRARIES "-ldrd -ldhd -lpthread -lusb-1.0 -lrt -ldl -lGL -lGLU -lglut")

catkin_package(
INCLUDE_DIRS include ${OMEGA6_LIBRARY_DIR}
#  LIBRARIES ur_teleop_master
#  CATKIN_DEPENDS other_catkin_pkg
  DEPENDS ${OMEGA6_LIBRARIES}
)

include_directories(
        include
        ${EIGEN3_INCLUDE_DIR}
)

# get all header files under include directory
file(GLOB HEADERS include "*.h")

add_library(haptic_device STATIC ${HEADERS} src/Button.cpp src/OmegaDevice.cpp)
target_link_libraries(haptic_device ${OMEGA6_LIBRARIES})

add_executable(example_friction_mode src/ExampleFrictionMode.cpp)
target_link_libraries(example_friction_mode haptic_device ${catkin_LIBRARIES} ${HEADERS})
