cmake_minimum_required(VERSION 3.6)

project(ESGRAF48 LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt5_wrap_ui(LOGO_TEST_UI
	mainwindow.ui
)

qt5_add_resources(LOGO_TEST_QRC
	mainwindow.qrc
)

set(DataModel_PROTO_FILES
	../proto/DataModel.proto
	../proto/V2SvkModel.proto
)

protobuf_generate_cpp(DataModel_PROTO_SRCS DataModel_PROTO_HDRS
	${DataModel_PROTO_FILES})

add_executable(${PROJECT_NAME} WIN32
	LogoTest.cpp
	DataModel.cpp
	mainwindow.cpp
	Age.cpp
	${LOGO_TEST_UI}
	${LOGO_TEST_QRC}
	${DataModel_PROTO_SRCS}
	${DataModel_PROTO_HDRS}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
		${CMAKE_CURRENT_BINARY_DIR}
		${Protobuf_INCLUDE_DIRS}
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
		${Protobuf_LIBRARIES}
)

add_subdirectory(CheckableItem)
add_subdirectory(CheckableTest)
add_subdirectory(CheckableTestModel)

add_subdirectory(MetaData)
add_subdirectory(SubTests)

add_subdirectory(ResultWidget)
