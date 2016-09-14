# Require a minimum version of the CMake build configuration
cmake_minimum_required(VERSION 2.8.3)

project(catbot_control)

# Linking catkin dependency Packages to the project
find_package(catkin REQUIRED COMPONENTS
  roscpp rospy std_msgs sensor_msgs geometry_msgs
)

# Configuring the package to resolve any package dependencies of packages that depend on this package
catkin_package(
   INCLUDE_DIRS include
#  LIBRARIES catbot_control
   CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs geometry_msgs
#  DEPENDS system_lib
)

# add the include directories present in catkin_INCLUDE_DIRS macro to the package
# any other include directories that are used in the c++ files must be listed in here
include_directories(
  ${catkin_INCLUDE_DIRS}
)

# Declare an node named: teleop_node from the source file: src/teleop/catbot_teleop.cpp
add_executable(teleop_node src/teleop/catbot_teleop.cpp)

# Link libraries to the executable
target_link_libraries(teleop_node ${catkin_LIBRARIES})

add_executable(fourWD_controller src/4WD_control.cpp)

# Link libraries to the executable
target_link_libraries(fourWD_controller ${catkin_LIBRARIES})
