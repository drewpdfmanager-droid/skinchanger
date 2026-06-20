cmake_minimum_required(VERSION 3.16)
project(SkinChangerLauncher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Add source files
set(SOURCES
    src/main.cpp
    src/requirements_checker.cpp
    src/project_builder.cpp
    src/downloader.cpp
)

# Create executable
add_executable(launcher ${SOURCES})

# Windows libraries
if(WIN32)
    target_link_libraries(launcher PRIVATE
        ws2_32
        wininet
        kernel32
    )
endif()

# Set output directory
set_target_properties(launcher PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Enable all warnings
if(MSVC)
    target_compile_options(launcher PRIVATE /W4)
else()
    target_compile_options(launcher PRIVATE -Wall -Wextra -Wpedantic)
endif()
