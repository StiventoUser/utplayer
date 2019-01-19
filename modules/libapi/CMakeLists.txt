set(PROJECT_NAME libapi)

set(HEADERS
	include/YtWrapper.h
	)

set(SOURCES
	src/YtWrapper.cpp
	)

add_library(${PROJECT_NAME}
	${HEADERS}
	${SOURCES}
	)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
#		CONAN_PKG::cpprestsdk
	)

make_fs_source_group_for_target(${PROJECT_NAME})
