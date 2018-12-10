cmake_minimum_required(VERSION 3.6)

project(LateSkills LANGUAGES CXX)

find_package(Qt5Widgets REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(UI_HEADERS 
	LateSkillsWidget.ui
)

set(LateSkills_PROTO_FILES
	../../../proto/LateSkillsGenitivModel.proto
	../../../proto/LateSkillsPassivModel.proto
)

protobuf_generate_cpp(LateSkills_PROTO_SRCS LateSkills_PROTO_HDRS 
	${LateSkills_PROTO_FILES}
)

add_library(${PROJECT_NAME}
	LateSkillsWidget.cpp
	LateSkillsModel.cpp
	PassivModel.cpp
	GenitivModel.cpp
	${UI_HEADERS}
	${LateSkills_PROTO_SRCS}
	${LateSkills_PROTO_HDRS}
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
