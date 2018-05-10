cmake_minimum_required(VERSION 3.6)

project(LogoTest LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(UI_HEADERS 
	mainwindow.ui
)

add_executable(${PROJECT_NAME}
	LogoTest.cpp
	mainwindow.cpp
	${UI_HEADERS}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt5::Widgets
)
