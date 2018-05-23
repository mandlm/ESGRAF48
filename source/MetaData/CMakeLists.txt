cmake_minimum_required(VERSION 3.6)

project(MetaData LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(META_DATA_UI
	MetaDataWidget.ui
)

add_library(${PROJECT_NAME}
	MetaDataModel.cpp
	MetaDataWidget.cpp
	${META_DATA_UI}
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
		Qt5::Widgets
)
