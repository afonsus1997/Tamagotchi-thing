cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME TamagotchiThing)
project(${CMAKE_PROJECT_NAME})
message("Build type: ${CMAKE_BUILD_TYPE}")

enable_language(C ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# --- U8g2 integration begins here ---

# Gather all .c files under Core/Src/u8g2 recursively
file(GLOB_RECURSE U8G2_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/u8g2/*.c
)

file(GLOB_RECURSE LIBMCU_BUTTON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/button/src/*.c
)

file(GLOB_RECURSE LIBMCU_COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/common/src/*.c
)

file(GLOB_RECURSE LIBMCU_LOGGING_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/logging/src/*.c
)

# Add U8g2 sources to target
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${U8G2_SOURCES}
    ${LIBMCU_BUTTON_SOURCES}
    ${LIBMCU_COMMON_SOURCES}
    ${LIBMCU_LOGGING_SOURCES}
    
    Core/Src/ssd1306.c
    Core/Src/u8g2_stm32L0.c
    Core/Src/ui.c
    Core/Src/userio.c
)

# Add include path for U8g2 headers
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/u8g2
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/button/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/logging/include
)

# --- U8g2 integration ends here ---

# Link directories (if needed)
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add custom lib search paths here
)

# Compile definitions (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Optional: Add macros like U8G2_USE_HW_I2C here
)

# Fix linker errors with libob.a if using C++
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Link with STM32 HAL and other libs
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
)
