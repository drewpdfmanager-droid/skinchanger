cmake_minimum_required(VERSION 3.16)
project(CS2SkinChangerStandalone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Disable unnecessary features
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Source files
set(SOURCES
    src/main-standalone.cpp
    src/app/application.cpp
    src/game/game_integration.cpp
    src/manager/skinchanger_manager.cpp
    src/skinchanger/skinchanger.cpp
    src/skinchanger/skin_database.cpp
    src/memory/memory.cpp
    src/memory/pattern_scanner.cpp
    src/hooking/directx_hook.cpp
    src/injection/injection_engine.cpp
    src/anticheat/anticheat.cpp
    src/config/config.cpp
    src/overlay/overlay.cpp
    src/inventory/inventory_manager.cpp
    src/launcher/launcher.cpp
    src/ui/console.cpp
    src/utils/float_calculator.cpp
)

# Create executable - Standalone, no console window
add_executable(skinchanger WIN32 ${SOURCES})

# Include directories
target_include_directories(skinchanger PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Windows libraries - STATIC LINKING
if(WIN32)
    target_link_libraries(skinchanger PRIVATE
        ws2_32
        d3d11
        d3dcompiler
        dxgi
        kernel32
        ntdll
        psapi
        user32
        gdi32
        shell32
        advapi32
    )
    
    # Static runtime
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    
    set_target_properties(skinchanger PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

# Optimization flags
if(MSVC)
    target_compile_options(skinchanger PRIVATE 
        /O2           # Optimization
        /W4           # Warnings
        /permissive-  # Standards compliance
        /Zc:inline    # Remove unreferenced functions
        /fp:fast      # Fast floating point
    )
    set_target_properties(skinchanger PROPERTIES
        LINK_FLAGS "/LTCG /OPT:REF /OPT:ICF"
    )
endif()

# Output directory
set_target_properties(skinchanger PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Disable incremental linking for smaller size
set_target_properties(skinchanger PROPERTIES LINK_FLAGS_RELEASE "/INCREMENTAL:NO")
