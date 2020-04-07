cmake_minimum_required(VERSION 2.8.3)
project(simple_car_model)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  DIRECTORY ../../msgs/
  FILES
  VehicleState.msg
  VehicleMoveCommand.msg
  Waypoint.msg
  Trajectory.msg
  )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  )


catkin_package(
  CATKIN_DEPENDS message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES simple_car_model
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

link_directories( /usr/lib/x86_64-linux-gnu/ )

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ../../libs/basic/include/
  )

add_executable(${PROJECT_NAME}_node
  src/main.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${SFML_LIBRARIES}
  sfml-network
  sfml-system
  sfml-window
  sfml-graphics
  )
