cmake_minimum_required(VERSION 2.8.3)
project(adis16488)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  serial
  std_msgs
  tf
   message_generation
)

 add_service_files(
   FILES
   Write.srv
   Read.srv
 )

 generate_messages(
  DEPENDENCIES
  std_msgs
   )

catkin_package(
 INCLUDE_DIRS include
  LIBRARIES adis16488
  CATKIN_DEPENDS roscpp rospy serial std_msgs  message_runtime 
  DEPENDS system_lib 
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

include_directories(include)

install(FILES include/adis16488/adis_interface.h include/adis16488/mathematics_operations.h
	include/adis16488/moving_average.h
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/adis16488)
  

add_executable(adis16488_node src/adis16488_node.cpp src/adis_interface.cpp src/mathematics_operations.cpp src/moving_average.cpp)
target_link_libraries(adis16488_node ${catkin_LIBRARIES})
add_dependencies(adis16488_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(adis_broadcaster src/adis_broadcaster.cpp)
target_link_libraries(adis_broadcaster ${catkin_LIBRARIES})
