cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt
	BASIC_SETUP
	BUILD missing
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(source)
add_subdirectory(test)
