cmake_minimum_required(VERSION 3.6)

project(ESGRAF48 LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt5_wrap_ui(LOGO_TEST_UI
	mainwindow.ui
)

qt5_add_resources(LOGO_TEST_QRC
	mainwindow.qrc
)

add_executable(${PROJECT_NAME} WIN32
	LogoTest.cpp
	DataModel.cpp
	mainwindow.cpp
	Age.cpp
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
		CheckableItem
		CheckableTest
		CheckableTestModel
		MetaData
		VerbEnd
		Plural
		Genus
		AkkusativDativ
		V2Svk
		LateSkills
		ResultWidget
		Qt5::Widgets
		Qt5::PrintSupport
)

add_subdirectory(CheckableItem)
add_subdirectory(CheckableTest)
add_subdirectory(CheckableTestModel)

add_subdirectory(MetaData)
add_subdirectory(SubTests)

add_subdirectory(ResultWidget)
