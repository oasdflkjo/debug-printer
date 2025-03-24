cmake_minimum_required(VERSION 3.16)
project(hardpanel_driver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_library(hardpanel_driver SHARED
    src/driver.cpp
    src/bluetooth.cpp
    src/parser.cpp
)

# Include directories
target_include_directories(hardpanel_driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Windows-specific settings
if(WIN32)
    target_compile_definitions(hardpanel_driver PRIVATE
        WIN32_LEAN_AND_MEAN
    )
endif()

# Link against Windows libraries
target_link_libraries(hardpanel_driver PRIVATE
    setupapi
    bluetoothapis
) 