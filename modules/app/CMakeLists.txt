set(PROJECT_NAME App)

find_package(Qt5
	COMPONENTS
		Core
		Quick
		QuickControls2
	REQUIRED
	)

include(${CMAKE_SOURCE_DIR}/Config.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ApiConfig.h.in ApiConfig.h @ONLY)

set(HEADERS
	)

set(SOURCES
	src/main.cpp
	)

set(QML
	qml/BrowseView.qml
	qml/LeftBrowsePanel.qml
	qml/main.qml
	qml/SearchFieldItem.qml
	qml/TopBrowsePanel.qml
	qml/UserButton.qml
	qml/VideoRectangleDelegate.qml
	qml/VideosView.qml
	)

set(GENERATED_FILES
	${CMAKE_CURRENT_BINARY_DIR}/ApiConfig.h
	)

add_executable(${PROJECT_NAME}
	${HEADERS}
	${SOURCES}
	${QML}
	"qml.qrc"
	${GENERATED_FILES}
	)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
	)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		include
		${CMAKE_CURRENT_BINARY_DIR}
	)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		libapi
		Qt5::Core
		Qt5::Quick
		Qt5::QuickControls2
	)

make_fs_source_group_for_target(${PROJECT_NAME})
