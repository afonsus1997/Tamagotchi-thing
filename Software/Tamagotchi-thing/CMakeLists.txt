cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(TamagotchiThing)
message("Build type: ${CMAKE_BUILD_TYPE}")

enable_language(C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(${PROJECT_NAME})

# Include the STM32CubeMX generated sources and HAL
add_subdirectory(cmake/stm32cubemx)

# Gather U8g2 related sources
file(GLOB_RECURSE U8G2_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/u8g2/*.c
)

# Gather libmcu modules sources
file(GLOB_RECURSE LIBMCU_COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/common/src/*.c
)
file(GLOB_RECURSE LIBMCU_LOGGING_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/logging/src/*.c
)

file(GLOB_RECURSE LWBTN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/lwbtn/lwbtn/src/lwbtn/*.c
)

file(GLOB_RECURSE TAMALIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/tamalib/*.c
)

# Your project source files
set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Proprietary/rom_12bit.c # For tama binary
    Core/Src/userio/userio.c
    Core/Src/ui/ui.c
    Core/Src/ui/forms.c
    Core/Src/usb/usb_user.c
    Core/Src/usb/usb_descriptors.c
    Core/Src/usb/usb_user_cdc.c 
    Core/Src/flash/flash.c
    Core/Src/flash/flash_glue.c
    Core/Src/tama_user/tama_user.c
    Core/Src/tama_user/tama_storage.c
    Core/Src/ssd1306.c
    Core/Src/log/log.c
    Core/Src/u8g2_stm32L0.c
)

# TinyUSB middleware sources
file(GLOB_RECURSE TINYUSB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/class/cdc/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/class/msc/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/portable/stm32/stm32l0/*.c
)

# Add all sources to target
target_sources(${PROJECT_NAME} PRIVATE
    ${U8G2_SOURCES}
    ${LIBMCU_COMMON_SOURCES}
    ${LIBMCU_LOGGING_SOURCES}
    ${PROJECT_SOURCES}
    ${TINYUSB_SOURCES}
    ${LWBTN_SOURCES}
    ${TAMALIB_SOURCES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/u8g2
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/libmcu/libmcu/modules/logging/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/userio
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/usb
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/flash
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/log
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/class/cdc
    # ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/class/msc
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/tinyusb/src/portable/stm32/stm32l0
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/lwbtn/lwbtn/src/include/lwbtn
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/lwbtn/lwbtn/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/tamalib
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/tama_user
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/Proprietary # For tama binary
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    CFG_TUSB_MCU=OPT_MCU_STM32L0
    CFG_TUSB_OS=OPT_OS_NONE
    CFG_TUD_CDC=1
    CFG_TUD_MSC=0
    CFG_TUD_VENDOR=0
    LWBTN_IGNORE_USER_OPTS=1
)


# Link libraries (STM32CubeMX and HAL libs)
target_link_libraries(${PROJECT_NAME}
    stm32cubemx
)
