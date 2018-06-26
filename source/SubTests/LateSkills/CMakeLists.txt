cmake_minimum_required(VERSION 3.6)

project(LateSkills LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(UI_HEADERS 
        LateSkillsWidget.ui
)

add_library(${PROJECT_NAME}
        LateSkillsWidget.cpp
	PassivModel.cpp
	GenitivModel.cpp
	${UI_HEADERS}
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
		CheckableItem
		CheckableTest
		CheckableTestModel
		Qt5::Widgets
)
