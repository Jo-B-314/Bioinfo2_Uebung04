cmake_minimum_required(VERSION 2.8.12)

project(Uebung04)

# Add C++ compile flags
set(CXX_FLAGS
    -std=c++14               # Use C++14
    -pedantic
    -Wall
)

# Set CIP Pool specific include paths
set(INSTALLER_PATH /installer/import/debian/c++)
set(CIP_STD_LIBS c++ c++abi m c gcc_s gcc)
set(GTEST_SRC_DIR ${INSTALLER_PATH}/googletest-1.7.0)

link_directories(${INSTALLER_PATH}/libcxx/lib)

# Find packages
include_directories(
        "${CMAKE_SOURCE_DIR}"
        "${CMAKE_BINARY_DIR}"
)
add_definitions(${CXX_FLAGS})

# Enable testing
enable_testing()

# Find Boost
find_package(Boost 1.55.0 COMPONENTS iostreams filesystem system program_options REQUIRED)

if(NOT Boost_FOUND)
        message(FATAL_ERROR "Boost version 1.55.0 or higher is required")
endif()

SET(Boost_LIBRARIES
        ${Boost_IOSTREAMS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
)

include_directories(${Boost_INCLUDE_DIRS})

# Add a new library, which is used for the executable below and
# for the tests in test/CMakeLists.txt
# Here, you can also add new files to your project
add_library(oralib SHARED
        OverRepresentationAnalysis.hpp
        OverRepresentationAnalysis.cpp
)

target_link_libraries(oralib)


# Add new program example1
# Here, you can also add new programs
add_executable(ora ora.cpp)
target_link_libraries(ora oralib)

add_subdirectory(tests)
