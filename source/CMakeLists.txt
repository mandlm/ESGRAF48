cmake_minimum_required(VERSION 3.6)

project(LogoTest LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt5_wrap_ui(LOGO_TEST_UI
	mainwindow.ui
)

qt5_add_resources(LOGO_TEST_QRC
	mainwindow.qrc
)

add_executable(${PROJECT_NAME}
	LogoTest.cpp
	DataModel.cpp
	mainwindow.cpp
	${LOGO_TEST_UI}
	${LOGO_TEST_QRC}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
		${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		MetaData
		VerbEnd
		Genus
		Qt5::Widgets
)

add_subdirectory(MetaData)
add_subdirectory(VerbEnd)
add_subdirectory(Genus)
