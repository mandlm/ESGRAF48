cmake_minimum_required(VERSION 3.6)

project(V2Svk LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(UI_HEADERS 
	V2SvkWidget.ui
)

set(V2Svk_PROTO_FILES
	../../../proto/V2SvkModel.proto
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${V2Svk_PROTO_FILES})

add_library(${PROJECT_NAME}
	V2SvkWidget.cpp
	V2SvkModel.cpp
	${UI_HEADERS}
	${PROTO_SRCS}
	${PROTO_HDRS}
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
