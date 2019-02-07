cmake_minimum_required(VERSION 3.6)

set(BUILD_VERSION_MAJOR_MINOR 0.4)

if ($ENV{BUILD_NUMBER})
	set(BUILD_VERSION_PATCH $ENV{BUILD_NUMBER})
else()
	set(BUILD_VERSION_PATCH 0)
endif()

project(ESGRAF48
	VERSION ${BUILD_VERSION_MAJOR_MINOR}.${BUILD_VERSION_PATCH}
	DESCRIPTION "ESGRAF 4-8"
	LANGUAGES CXX
)

configure_file(
	version.h.in
	version.h
)


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
	../proto/MetaDataModel.proto
	../proto/V2SvkModel.proto
	../proto/VerbEndModel.proto
	../proto/GenusModel.proto
	../proto/AkkusativModel.proto
	../proto/DativModel.proto
	../proto/PluralModel.proto
	../proto/LateSkillsPassivModel.proto
	../proto/LateSkillsGenitivModel.proto
)

protobuf_generate_cpp(DataModel_PROTO_SRCS DataModel_PROTO_HDRS
	${DataModel_PROTO_FILES})

add_executable(${PROJECT_NAME} WIN32
	ESGRAF48.cpp
	DataModel.cpp
	mainwindow.cpp
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
		Age
		CheckableItem
		CheckableTest
		CheckableTestModel
		PrintableModel
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

add_subdirectory(Age)
add_subdirectory(CheckableItem)
add_subdirectory(CheckableTest)
add_subdirectory(CheckableTestModel)
add_subdirectory(PrintableModel)

add_subdirectory(MetaData)
add_subdirectory(SubTests)

add_subdirectory(ResultWidget)
