cmake_minimum_required(VERSION 2.8.3)
project(waypoint_box)

#find_package(Boost COMPONENTS program_options REQUIRED)
#find_package(OpenCV 3.3 COMPONENTS core highgui imgproc REQUIRED)
#find_package(OpenCV COMPONENTS core highgui imgproc REQUIRED)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

add_definitions(-std=c++11)

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
#  LIBRARIES test
  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(
	waypoint_box_node
	src/waypoint_box_node.cpp)

target_link_libraries(
	waypoint_box_node
	${catkin_LIBRARIES}
    ${OpenCV_LIBS}  
)
