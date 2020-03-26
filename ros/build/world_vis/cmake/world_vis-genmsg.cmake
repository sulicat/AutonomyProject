# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "world_vis: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iworld_vis:/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs/;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(world_vis_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_custom_target(_world_vis_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "world_vis" "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg" NAME_WE)
add_custom_target(_world_vis_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "world_vis" "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg" "geometry_msgs/Vector3:std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(world_vis
  "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/world_vis
)
_generate_msg_cpp(world_vis
  "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/world_vis
)

### Generating Services

### Generating Module File
_generate_module_cpp(world_vis
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/world_vis
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(world_vis_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(world_vis_generate_messages world_vis_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_dependencies(world_vis_generate_messages_cpp _world_vis_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg" NAME_WE)
add_dependencies(world_vis_generate_messages_cpp _world_vis_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(world_vis_gencpp)
add_dependencies(world_vis_gencpp world_vis_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS world_vis_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(world_vis
  "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/world_vis
)
_generate_msg_lisp(world_vis
  "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/world_vis
)

### Generating Services

### Generating Module File
_generate_module_lisp(world_vis
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/world_vis
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(world_vis_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(world_vis_generate_messages world_vis_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_dependencies(world_vis_generate_messages_lisp _world_vis_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg" NAME_WE)
add_dependencies(world_vis_generate_messages_lisp _world_vis_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(world_vis_genlisp)
add_dependencies(world_vis_genlisp world_vis_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS world_vis_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(world_vis
  "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/world_vis
)
_generate_msg_py(world_vis
  "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/world_vis
)

### Generating Services

### Generating Module File
_generate_module_py(world_vis
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/world_vis
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(world_vis_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(world_vis_generate_messages world_vis_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_dependencies(world_vis_generate_messages_py _world_vis_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/world_vis/../../msgs//VehicleState.msg" NAME_WE)
add_dependencies(world_vis_generate_messages_py _world_vis_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(world_vis_genpy)
add_dependencies(world_vis_genpy world_vis_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS world_vis_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/world_vis)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/world_vis
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(world_vis_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(world_vis_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/world_vis)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/world_vis
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(world_vis_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(world_vis_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/world_vis)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/world_vis\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/world_vis
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(world_vis_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(world_vis_generate_messages_py geometry_msgs_generate_messages_py)
endif()
