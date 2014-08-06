# So CMake can tell whether or not it can process this file
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
project(smokeos C ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")

set(TEST "hello")

# Grab all of the C files in src; store in C_SRCS
FILE(GLOB C_SRCS src/*.c)

add_library(A OBJECT ${C_SRCS})
add_library(B OBJECT src/kernel_start_gas.s)

# Note how we obtain this variable's value!
ADD_EXECUTABLE(kernel $<TARGET_OBJECTS:B> $<TARGET_OBJECTS:A>)
SET_TARGET_PROPERTIES(kernel PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.bin" LINK_FLAGS 
  "-T ${PROJECT_SOURCE_DIR}/link.ld -nostartfiles")

SET(ADDITIONAL_MAKE_CLEAN_FILES isodir smokeos.iso)

ADD_CUSTOM_TARGET(iso
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot
    COMMAND COMMAND ${CMAKE_COMMAND} -E copy smokeos.bin ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/smokeos.bin
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/grub/grub.cfg
    COMMAND ${CMAKE_COMMAND} -E echo "Creating ISO..."
    COMMAND grub-mkrescue -o smokeos.iso ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir > /dev/null 2>&1
    DEPENDS kernel)

ADD_CUSTOM_TARGET(astyle
    COMMAND astyle --options=${CMAKE_SOURCE_DIR}/astylerc \"${CMAKE_SOURCE_DIR}/src/*.c\" \"${CMAKE_SOURCE_DIR}/src/*.h\")