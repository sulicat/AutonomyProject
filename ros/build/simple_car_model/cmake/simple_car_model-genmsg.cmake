# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "simple_car_model: 2 messages, 0 services")

set(MSG_I_FLAGS "-Isimple_car_model:/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs/;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(simple_car_model_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg" NAME_WE)
add_custom_target(_simple_car_model_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "simple_car_model" "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg" "geometry_msgs/Vector3:std_msgs/Header"
)

get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_custom_target(_simple_car_model_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "simple_car_model" "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg" "std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(simple_car_model
  "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simple_car_model
)
_generate_msg_cpp(simple_car_model
  "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simple_car_model
)

### Generating Services

### Generating Module File
_generate_module_cpp(simple_car_model
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simple_car_model
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(simple_car_model_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(simple_car_model_generate_messages simple_car_model_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg" NAME_WE)
add_dependencies(simple_car_model_generate_messages_cpp _simple_car_model_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_dependencies(simple_car_model_generate_messages_cpp _simple_car_model_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simple_car_model_gencpp)
add_dependencies(simple_car_model_gencpp simple_car_model_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simple_car_model_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(simple_car_model
  "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simple_car_model
)
_generate_msg_lisp(simple_car_model
  "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simple_car_model
)

### Generating Services

### Generating Module File
_generate_module_lisp(simple_car_model
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simple_car_model
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(simple_car_model_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(simple_car_model_generate_messages simple_car_model_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg" NAME_WE)
add_dependencies(simple_car_model_generate_messages_lisp _simple_car_model_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_dependencies(simple_car_model_generate_messages_lisp _simple_car_model_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simple_car_model_genlisp)
add_dependencies(simple_car_model_genlisp simple_car_model_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simple_car_model_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(simple_car_model
  "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simple_car_model
)
_generate_msg_py(simple_car_model
  "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simple_car_model
)

### Generating Services

### Generating Module File
_generate_module_py(simple_car_model
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simple_car_model
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(simple_car_model_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(simple_car_model_generate_messages simple_car_model_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleState.msg" NAME_WE)
add_dependencies(simple_car_model_generate_messages_py _simple_car_model_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/oavillanueva/AutonomyProject/ros/src/simple_car_model/../../msgs//VehicleMoveCommand.msg" NAME_WE)
add_dependencies(simple_car_model_generate_messages_py _simple_car_model_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(simple_car_model_genpy)
add_dependencies(simple_car_model_genpy simple_car_model_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS simple_car_model_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simple_car_model)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/simple_car_model
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(simple_car_model_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(simple_car_model_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simple_car_model)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/simple_car_model
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(simple_car_model_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(simple_car_model_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simple_car_model)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simple_car_model\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/simple_car_model
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(simple_car_model_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(simple_car_model_generate_messages_py geometry_msgs_generate_messages_py)
endif()
