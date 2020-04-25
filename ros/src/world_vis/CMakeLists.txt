cmake_minimum_required(VERSION 2.8.3)
project(world_vis)

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

find_package(Freetype REQUIRED)

find_package(OpenGL REQUIRED)

## Generate messages in the 'msg' folder
add_message_files(
  DIRECTORY ../../msgs/
  FILES
  VehicleState.msg
  VehicleMoveCommand.msg
  Waypoint.msg
  Trajectory.msg
  Obstacle.msg
  ObstacleList.msg
  CostMap.msg
  Line.msg
  RenderTree.msg
  PID_Gains.msg
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

set(IMGUI_DIR ../../libs/imgui)
set(IMGUI_SFML_DIR ../../libs/imgui_sfml)

file(GLOB_RECURSE IMGUI_SRC
    ${IMGUI_DIR}/*.h
    ${IMGUI_DIR}/*.cpp
)


catkin_package(
  CATKIN_DEPENDS message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES world_vis
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

link_directories( ../../libs/SFML-2.5.1/lib/ )


## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ../../libs/basic/include/
  ../../libs/SFML-2.5.1/include/
  ${IMGUI_DIR}
  ${IMGUI_DIR}/misc
  ${IMGUI_SFML_DIR}
  ${FREETYPE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  )

add_executable(${PROJECT_NAME}_node
  src/main.cpp
  src/gui.cpp
  src/world.cpp
  src/ros_to_system.cpp
  ../../libs/basic/src/BaseVehicle.cpp
  ${IMGUI_SRC}
  ${IMGUI_SFML_DIR}/imgui-SFML.cpp
)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${SFML_LIBRARIES}
  ${FREETYPE_LIBRARIES}
  sfml-network
  sfml-system
  sfml-window
  sfml-graphics
  ${OPENGL_LIBRARIES}
  )

add_dependencies( ${PROJECT_NAME}_node
  ${catkin_EXPORTED_TARGETS} )

add_dependencies(${PROJECT_NAME}_node ${PROJECT_NAME}_generate_messages_cpp)
