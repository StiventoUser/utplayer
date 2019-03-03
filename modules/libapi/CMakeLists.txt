set(PROJECT_NAME libapi)

find_package(Qt5
	COMPONENTS
		Core
		Gui
	REQUIRED
	)

set(HEADERS
	include/api/ApiRequest.h
	include/api/ApiResponse.h
	include/api/GApiAccessData.h
	include/api/GApiCommandExecutor.h
	include/api/GApiWrapper.h
	include/api/OAuth2Session.h
	include/api/OAuth2GApiSession.h
	include/api/UserProfile.h
	include/api/Utils.h
	)

set(COMMANDS_HEADERS
	include/api/commands/Command.h
	include/api/commands/GetMostPopular.h
	)

set(MODELS_HEADERS
	include/api/models/KeyValueModel.h
	include/api/models/KeyValueModelVectorModel.h
	)

set(SOURCES
	src/ApiRequest.cpp
	src/ApiResponse.cpp
	src/GApiAccessData.cpp
	src/GApiCommandExecutor.cpp
	src/GApiWrapper.cpp
	src/OAuth2Session.cpp
	src/OAuth2GApiSession.cpp
	src/UserProfile.cpp
	src/Utils.cpp
	)

set(COMMANDS_SOURCES
	src/commands/Command.cpp
	src/commands/GetMostPopular.cpp
	)

set(MODELS_SOURCES
	src/models/KeyValueModel.cpp
	src/models/KeyValueModelVectorModel.cpp
	)

add_library(${PROJECT_NAME}
	${HEADERS}
	${COMMANDS_HEADERS}
	${MODELS_HEADERS}
	${SOURCES}
	${COMMANDS_SOURCES}
	${MODELS_SOURCES}
	)

target_compile_definitions(${PROJECT_NAME}
	PUBLIC
		-D_TURN_OFF_PLATFORM_STRING
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
		CONAN_PKG::jsonformoderncpp
	)

make_fs_source_group_for_target(${PROJECT_NAME})
