# So CMake can tell whether or not it can process this file
cmake_minimum_required(VERSION 2.8.0)
INCLUDE(CMakeForceCompiler)
project(smokeos C ASM)
set(PLATFORM "x86")

if(${PLATFORM} STREQUAL "x86")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32  -fno-builtin")
    set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")
    set(LD_OPTS "-T ${PROJECT_SOURCE_DIR}/link.ld -nostartfiles")

    add_custom_target(iso
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot
        COMMAND COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}.bin ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/${PROJECT_NAME}.bin
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/grub/grub.cfg
        COMMAND ${CMAKE_COMMAND} -E echo "Creating ISO..."
        COMMAND grub-mkrescue -o ${PROJECT_NAME}.iso ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir > /dev/null 2>&1
        DEPENDS kernel)
elseif(${PLATFORM} STREQUAL "gba")
    CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
    set(PREFIX "arm-none-eabi-")
    SET (CMAKE_ASM_COMPILE_OBJECT "arm-none-eabi-gcc <FLAGS> -c -o <OBJECT> <SOURCE>") 
    set(CMAKE_C_FLAGS "-Os")
    set(LD_OPTS "-nostdlib -specs gba.specs")
    SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
elseif(${PLATFORM} STREQUAL "sparc")
    CMAKE_FORCE_C_COMPILER(sparc64-linux-gnu-gcc GNU)
    set(PREFIX "sparc64-linux-gnu-")
    SET (CMAKE_ASM_COMPILE_OBJECT "sparc64-linux-gnu-gcc <FLAGS> -c -o <OBJECT> <SOURCE>") 
    set(CMAKE_C_FLAGS "-fno-builtin -nostdlib")
    set(LD_OPTS "-nostdlib -T sparcboot.ld")
    SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
endif()

# Grab all of the C files in src; store in C_SRCS
file(GLOB C_SRCS ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/${PLATFORM}/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/include/ ${CMAKE_SOURCE_DIR}/src/${PLATFORM}/include/)

add_library(A OBJECT ${C_SRCS})
add_library(B OBJECT ${CMAKE_SOURCE_DIR}/src/${PLATFORM}/boot.s)

# Note how we obtain this variable's value!
add_executable(kernel $<TARGET_OBJECTS:B> $<TARGET_OBJECTS:A>)
set_target_properties(kernel PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.bin" LINK_FLAGS "${LD_OPTS}")

#set(ADDITIONAL_MAKE_CLEAN_FILES isodir ${PROJECT_NAME}.iso)
#add_executable(kernel ${CMAKE_SOURCE_DIR}/src/kernel.c)
#set_target_properties(kernel PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.bin" LINK_FLAGS "${LD_OPTS}")

add_custom_target(astyle
    COMMAND astyle --options=${CMAKE_SOURCE_DIR}/astylerc \"${CMAKE_SOURCE_DIR}/src/*.c\" \"${CMAKE_SOURCE_DIR}/src/*.h\")