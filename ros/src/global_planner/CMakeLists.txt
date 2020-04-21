cmake_minimum_required(VERSION 2.8.3)
project(global_planner)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  message_generation
  roscpp
  std_msgs
)


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
  )

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  )

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ../../libs/basic/include/
)

add_executable( ${PROJECT_NAME}_node
  src/global_planner.cpp
  src/node.cpp
  src/main.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  )


add_dependencies( ${PROJECT_NAME}_node
  ${catkin_EXPORTED_TARGETS} )

add_dependencies(${PROJECT_NAME}_node ${PROJECT_NAME}_generate_messages_cpp)

