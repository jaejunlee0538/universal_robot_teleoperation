cmake_minimum_required(VERSION 2.8.3)
project(ur_teleop_ros_client)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
        roscpp
        ur_teleop_commons
        ur_teleop_messages
        )


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
        #  INCLUDE_DIRS include
        #  LIBRARIES ur_teleop_ros_client
          CATKIN_DEPENDS ur_teleop_commons ur_teleop_messages roscpp
        #  DEPENDS system_lib
)

include_directories(
        ${catkin_INCLUDE_DIRS}
        include
        ../ur_control_box
)

## Declare a C++ library
add_library(ur_teleop_ur_ros_client
        src/URRosClient.cpp
        src/URCallbackClient.cpp
        )
add_library(ur_teleop_ur_message
        ../ur_control_box/ur_messages/RobotStateMessage.cpp
        ../ur_control_box/ur_messages/ConfigCommandMessage.cpp
        ../ur_control_box/ur_messages/JointCommandMessage.cpp
        ../ur_control_box/ur_messages/cmd_utils.cpp
        )

add_executable(main_ur_ros_client
        src/main_ur_ros_clinent.cpp)
target_link_libraries(main_ur_ros_client
        ur_teleop_ur_ros_client
        ur_teleop_ur_message
        ${catkin_LIBRARIES})