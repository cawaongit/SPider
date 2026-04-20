cmake_minimum_required(VERSION 3.10)

project(spider)

add_executable(spider
	main.c
)

target_include_directories(spider PRIVATE include)

target_link_libraries(spider PRIVATE
	wiringPi
	${CMAKE_SOURCE_DIR}/lib/pca9685.o
)
