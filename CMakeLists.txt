cmake_minimum_required(VERSION 3.10)

project(SPider)

add_executable(SPider
	main.cpp
)

find_package(OpenCV REQUIRED)

target_include_directories(SPider PRIVATE 
	include
	${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(SPider PRIVATE
	wiringPi
	${CMAKE_SOURCE_DIR}/lib/pca9685.o
	${OpenCV_LIBS}
)
