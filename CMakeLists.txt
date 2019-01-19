cmake_minimum_required(VERSION 3.4)

project(utplayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/utils.cmake)

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
		jsonformoderncpp/3.5.0@vthiery/stable
	BASIC_SETUP CMAKE_TARGETS
	BUILD missing
	)

add_subdirectory(modules/app)
add_subdirectory(modules/libapi)
