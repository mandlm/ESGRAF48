cmake_minimum_required(VERSION 3.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt
	BASIC_SETUP
	BUILD missing
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
	message(STATUS "clang-tidy found in ${CLANG_TIDY_EXE}")
	set(CMAKE_CXX_CLANG_TIDY= "${CLANG_TIDY_EXE}")
else()
	message(WARNING "clang-tidy missing, no checks!")
endif()

add_subdirectory(source)
#add_subdirectory(test)
