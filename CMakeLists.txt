# So CMake can tell whether or not it can process this file
cmake_minimum_required(VERSION 2.8.0)
project(smokeos C ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")

# Grab all of the C files in src; store in C_SRCS
file(GLOB C_SRCS src/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/include/)

add_library(A OBJECT ${C_SRCS})
add_library(B OBJECT src/kernel_start_gas.s)

# Note how we obtain this variable's value!
add_executable(kernel $<TARGET_OBJECTS:B> $<TARGET_OBJECTS:A>)
set_target_properties(kernel PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.bin" LINK_FLAGS 
  "-T ${PROJECT_SOURCE_DIR}/link.ld -nostartfiles")

set(ADDITIONAL_MAKE_CLEAN_FILES isodir ${PROJECT_NAME}.iso)

add_custom_target(iso
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot
    COMMAND COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}.bin ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir/boot/grub/grub.cfg
    COMMAND ${CMAKE_COMMAND} -E echo "Creating ISO..."
    COMMAND grub-mkrescue -o ${PROJECT_NAME}.iso ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/isodir > /dev/null 2>&1
    DEPENDS kernel)

add_custom_target(astyle
    COMMAND astyle --options=${CMAKE_SOURCE_DIR}/astylerc \"${CMAKE_SOURCE_DIR}/src/*.c\" \"${CMAKE_SOURCE_DIR}/src/*.h\")