cmake_minimum_required(VERSION 2.8.3)
project(ur_teleop_commons)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES ur_teleop_serialize ur_teleop_socket ur_teleop_utils
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
  include
)

add_library(ur_teleop_serialize 
	src/ByteBuffer.cpp
	src/ByteBufferEndian.cpp)

add_library(ur_teleop_socket
	src/SocketInterface.cpp
	src/UDPServer.cpp
	src/UDPClient.cpp
	src/UDPSocket.cpp)

add_library(ur_teleop_utils
	src/LoopInterface.cpp)
