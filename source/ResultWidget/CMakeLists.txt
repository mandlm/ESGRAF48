cmake_minimum_required(VERSION 3.6)

project(ResultWidget LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(GENUS_UI
        ResultWidget.ui
)

add_library(${PROJECT_NAME}
        ResultWidget.cpp
        ResultModel.cpp
		PRMap.cpp
	${GENUS_UI}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt5::Widgets
)
