﻿cmake_minimum_required(VERSION 3.20)
project("Knights and Merchants" VERSION 1.0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################################################################################
# Install Google Test
#######################################################################################

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#######################################################################################
# Definitions of source and header files
#######################################################################################

file(GLOB_RECURSE sources LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB_RECURSE tests LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

file(GLOB_RECURSE fheaders LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/api/inc/*.h)
file(GLOB_RECURSE dheaders LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/inc/*.h)

#######################################################################################
# Target KaM-Win-x86
#######################################################################################

add_executable(KaM-Win-x86 WIN32
        ${sources}
        ${headers}
        ${fheaders}
        ${dheaders}
)

target_include_directories(
        KaM-Win-x86
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/inc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/inc
)

target_link_libraries(
        KaM-Win-x86
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/ddraw.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dinput8.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dplayx.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/lib/x86/fmod.lib
        "Vfw32.lib"
)

add_custom_command(
        TARGET KaM-Win-x86 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/third_party/fmod/dll/fmod.dll $<TARGET_FILE_DIR:KaM-Win-x86>
)

add_custom_command(
        TARGET KaM-Win-x86 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:KaM-Win-x86>/data/
)

#######################################################################################
# Target KaM-Win-x64
#######################################################################################

add_executable(KaM-Win-x64 WIN32
        ${sources}
        ${headers}
        ${fheaders}
        ${dheaders}
)

target_include_directories(
        KaM-Win-x64
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/inc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/inc
)

target_link_libraries(
        KaM-Win-x64
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x64/ddraw.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x64/dinput8.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dplayx.lib

        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/lib/x64/fmod.lib
        "Vfw32.lib"
)

add_custom_command(
        TARGET KaM-Win-x64 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/third_party/fmod/dll/fmod64.dll $<TARGET_FILE_DIR:KaM-Win-x64>
)

add_custom_command(
        TARGET KaM-Win-x64 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:KaM-Win-x64>/data/
)

#######################################################################################
# Target KaM-Tests
#######################################################################################

add_executable(
        KaM-Tests
        ${sources}
        ${headers}
        ${fheaders}
        ${dheaders}
        ${tests}
)

target_link_libraries(
        KaM-Tests
        gtest_main
        gmock_main
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/ddraw.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dinput8.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dplayx.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/lib/x86/fmod.lib
        "Vfw32.lib"
)

target_include_directories(
        KaM-Tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/inc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/inc
)