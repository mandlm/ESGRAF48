cmake_minimum_required(VERSION 3.5)
project(run-tests)

find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME}
	main.cpp
	dummy.cpp
	Age.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Catch2::Catch2
		Age
)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

