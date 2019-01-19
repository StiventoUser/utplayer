cmake_minimum_required(VERSION 3.1)

project(utplayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Run conan on cmake configure step.
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
	REQUIRES
		cpprestsdk/2.10.2@bincrafters/stable
	BASIC_SETUP CMAKE_TARGETS
	BUILD missing
	)

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Network NetworkAuth REQUIRED)

file(GLOB HEADERS include/*)
file(GLOB SOURCES src/*)
file(GLOB QML qml/*)

add_executable(${PROJECT_NAME}
	${HEADERS}
	${SOURCES}
	"qml.qrc"
	)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
	)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt5::Core
		Qt5::Quick
		Qt5::QuickControls2
		Qt5::Network
		Qt5::NetworkAuth
		CONAN_PKG::cpprestsdk
	)

source_group(headers ${HEADERS})
source_group(sources ${SOURCES})
source_group(qml ${QML})
