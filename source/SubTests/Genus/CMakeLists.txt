cmake_minimum_required(VERSION 3.6)

project(Genus LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(GENUS_UI
	GenusWidget.ui
)


set(Genus_PROTO_FILES
	../../../proto/GenusModel.proto
)

protobuf_generate_cpp(Genus_PROTO_SRCS Genus_PROTO_HDRS ${Genus_PROTO_FILES})

add_library(${PROJECT_NAME}
	GenusWidget.cpp
	GenusModel.cpp
	${GENUS_UI}
	${Genus_PROTO_SRCS}
	${Genus_PROTO_HDRS}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
		${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		CheckableItem
		CheckableTest
		CheckableTestModel
		Qt5::Widgets
		${Protobuf_LIBRARIES}
)
