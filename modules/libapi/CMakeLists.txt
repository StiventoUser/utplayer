set(PROJECT_NAME libapi)

find_package(Qt5
	COMPONENTS
		Core
		Gui
	REQUIRED
	)

set(HEADERS
	include/api/OAuth2Session.h
	include/api/YtWrapper.h
	)

set(SOURCES
	src/OAuth2Session.cpp
	src/YtWrapper.cpp
	)

add_library(${PROJECT_NAME}
	${HEADERS}
	${SOURCES}
	)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
	)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Qt5::Core
		Qt5::Gui
		CONAN_PKG::cpprestsdk
	)

make_fs_source_group_for_target(${PROJECT_NAME})
