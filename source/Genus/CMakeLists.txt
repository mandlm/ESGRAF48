cmake_minimum_required(VERSION 3.6)

project(Genus LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(GENUS_UI
	GenusWidget.ui
)

add_library(${PROJECT_NAME}
	GenusWidget.cpp
	GenusModel.cpp
	${GENUS_UI}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
                CheckableItem
		Qt5::Widgets
)
