cmake_minimum_required(VERSION 3.10)

project(spider)

add_executable(spider
	moves.c
)

target_link_libraries(spider PRIVATE
	wiringPi
)
