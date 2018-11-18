cmake_minimum_required(VERSION 3.6)

project(MetaData LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(META_DATA_UI
	MetaDataWidget.ui
)

set(MetaDataModel_PROTO_FILES
	../../proto/MetaDataModel.proto
)

protobuf_generate_cpp(MetaDataModel_PROTO_SRCS MetaDataModel_PROTO_HDRS
	${MetaDataModel_PROTO_FILES}
)

add_library(${PROJECT_NAME}
	MetaDataModel.cpp
	MetaDataWidget.cpp
	${META_DATA_UI}
	${MetaDataModel_PROTO_SRCS}
	${MetaDataModel_PROTO_HDRS}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
		${Protobuf_INCLUDE_DIRS}
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt5::Widgets
		${Protobuf_LIBRARIES}
)
