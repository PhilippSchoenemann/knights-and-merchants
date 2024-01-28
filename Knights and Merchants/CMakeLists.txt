cmake_minimum_required(VERSION 3.27)
project("Knights and Merchants"
        VERSION 1.0.0.0
        DESCRIPTION "A classic real-time strategy (RTS) game set in a medieval world."
        LANGUAGES C CXX)

if (NOT WIN32)
    message(FATAL_ERROR "${PROJECT_NAME} is only supported on Windows.")
endif (NOT WIN32)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

include(ProcessorCount)
ProcessorCount(PROCESSOR_COUNT)

message(STATUS "Number of logical cores: ${PROCESSOR_COUNT}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################################################################################
# Google Test
#######################################################################################

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#######################################################################################
# Documentation
#######################################################################################

find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN  "${CMAKE_CURRENT_SOURCE_DIR}/documentation/Doxyfile.in")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(Documentation ALL
                      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      COMMENT "Generating API documentation with Doxygen"
                      VERBATIM)
endif (DOXYGEN_FOUND)

#######################################################################################
# Definitions of source and header files
#######################################################################################

set(sources
    src/AnimationEntry.cpp
    src/AnimationEntryEx.cpp
    src/Array.cpp
    src/ArrayBriefings.cpp
    src/ArrayUnk00.cpp
    src/ArrayUnkMap.cpp
    src/ClassyThree.cpp
    src/ClassyTwo.cpp
    src/DefinedSounds.cpp
    src/Globals.cpp
    src/Group.cpp
    src/GroupManager.cpp
    src/House.cpp
    src/HouseManager.cpp
    src/HousesDat.cpp
    src/InGame.cpp
    src/InterchangeFileFormat.cpp
    src/Map.cpp
    src/MasterClass.cpp
    src/MiniMapMaybe.cpp
    src/NetworkClass.cpp
    src/PlayerStatistic.cpp
    src/PlayerStatistics.cpp
    src/RandomGenerator.cpp
    src/Selection.cpp
    src/Settings.cpp
    src/Sound.cpp
    src/SoundManager.cpp
    src/StoreHouse.cpp
    src/StoreHouseManager.cpp
    src/Tile.cpp
    src/Unit.cpp
    src/UnitDat.cpp
    src/UnitManager.cpp
    src/UnkClass1000.cpp
    src/UnkClass2000.cpp
    src/UnkClass3000.cpp
    src/UnkClass670.cpp
    src/UnkClass671.cpp
    src/UnkClass700.cpp
    src/UnkClass800.cpp
    src/UnkClass900.cpp
    src/UnkGame1.cpp
    src/UnkGame111.cpp
    src/UnkGame2.cpp
    src/UnkGame20.cpp
    src/UnkGame3.cpp
    src/UnkGame5.cpp
    src/UnkGame6.cpp
    src/engine/GraphicsHandler.cpp
    src/engine/UnkGraphicsClass.cpp
    src/graphics/Bitmap.cpp
    src/graphics/DrawableSurface.cpp
    src/graphics/Font.cpp
    src/graphics/Palette.cpp
    src/graphics/RX.cpp
    src/io/FileIo.cpp
    src/io/InputHandler.cpp
    src/io/KeyboardHandler.cpp
    src/io/MouseHandler.cpp
    src/main.cpp
    src/media/AVIClass.cpp
    src/text/Lib.cpp
    src/ui/UnkClass200.cpp
    src/ui/UnkClass201.cpp
    src/ui/UnkClass202.cpp
    src/ui/UnkClass203.cpp
    src/ui/UnknownUICon.cpp
    src/ui/controls/Button.cpp
    src/ui/controls/ImageBox.cpp
    src/ui/controls/ScrollTextBox.cpp
    src/ui/controls/TextBox.cpp
    src/ui/controls/UIElement.cpp
    src/ui/controls/UnkClass674.cpp
    src/utilities/Parser.cpp
    src/utilities/Rect.cpp)

set(headers
    inc/AnimationEntry.h
    inc/AnimationEntryEx.h
    inc/Array.h
    inc/ArrayBriefings.h
    inc/ArrayUnk00.h
    inc/ArrayUnkMap.h
    inc/ClassyThree.h
    inc/ClassyTwo.h
    inc/DefinedSounds.h
    inc/Globals.h
    inc/Group.h
    inc/GroupManager.h
    inc/House.h
    inc/HouseManager.h
    inc/HousesDat.h
    inc/InGame.h
    inc/InterchangeFileFormat.h
    inc/Map.h
    inc/MasterClass.h
    inc/MiniMapMaybe.h
    inc/NetworkClass.h
    inc/PlayerStatistic.h
    inc/PlayerStatistics.h
    inc/RandomGenerator.h
    inc/Selection.h
    inc/Settings.h
    inc/Sound.h
    inc/SoundManager.h
    inc/StoreHouse.h
    inc/StoreHouseManager.h
    inc/Tile.h
    inc/Unit.h
    inc/UnitDat.h
    inc/UnitManager.h
    inc/UnkClass1000.h
    inc/UnkClass2000.h
    inc/UnkClass3000.h
    inc/UnkClass670.h
    inc/UnkClass671.h
    inc/UnkClass700.h
    inc/UnkClass800.h
    inc/UnkClass900.h
    inc/UnkGame1.h
    inc/UnkGame111.h
    inc/UnkGame2.h
    inc/UnkGame20.h
    inc/UnkGame3.h
    inc/UnkGame5.h
    inc/UnkGame6.h
    inc/engine/GraphicsHandler.h
    inc/engine/UnkGraphicsClass.h
    inc/engine/UnknownStruct.h
    inc/graphics/Bitmap.h
    inc/graphics/DrawableSurface.h
    inc/graphics/Font.h
    inc/graphics/Palette.h
    inc/graphics/RX.h
    inc/io/FileIo.h
    inc/io/InputHandler.h
    inc/io/IoException.h
    inc/io/KeyboardHandler.h
    inc/io/MouseHandler.h
    inc/media/AVIClass.h
    inc/text/Lib.h
    inc/ui/UnkClass200.h
    inc/ui/UnkClass201.h
    inc/ui/UnkClass202.h
    inc/ui/UnkClass203.h
    inc/ui/UnknownUICon.h
    inc/ui/controls/Button.h
    inc/ui/controls/ImageBox.h
    inc/ui/controls/ScrollTextBox.h
    inc/ui/controls/TextBox.h
    inc/ui/controls/UIElement.h
    inc/ui/controls/UnkClass674.h
    inc/utilities/DoublyLinkedList.h
    inc/utilities/Parser.h
    inc/utilities/Rect.h)

set(tests
    test/io/FileIo_Tests.cpp
    test/text/Lib_Tests.cpp
    test/utilities/Rect_Tests.cpp)

#######################################################################################
# Library Targets
#######################################################################################

add_library(FMOD_Static SHARED IMPORTED)
set_target_properties(FMOD_Static PROPERTIES
                      IMPORTED_LOCATION             "${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/dll/fmod.lib"
                      IMPORTED_IMPLIB               "${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/lib/x86/fmod.lib"
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmod/inc")

add_library(DIRECTX_Static STATIC IMPORTED)
set_target_properties(DIRECTX_Static PROPERTIES
                      IMPORTED_LOCATION                 "${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/ddraw.lib"
                      IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dinput8.lib;${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/lib/x86/dplayx.lib"
                      INTERFACE_INCLUDE_DIRECTORIES     "${CMAKE_CURRENT_SOURCE_DIR}/third_party/directx/inc")

#######################################################################################
# Target KaM
#######################################################################################

add_executable(KaM WIN32 ${sources} ${headers})

target_include_directories(KaM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(KaM
                      FMOD_Static
                      DIRECTX_Static
                      "Vfw32.lib")

add_custom_command(TARGET KaM POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/third_party/fmod/dll/fmod.dll $<TARGET_FILE_DIR:KaM>)

add_custom_command(TARGET KaM POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:KaM>/data/)

#######################################################################################
# Target AllTests
#######################################################################################

add_executable(AllTests ${sources} ${headers} ${tests})

target_link_libraries(AllTests
                      gtest_main
                      gmock_main
                      FMOD_Static
                      DIRECTX_Static
                      "Vfw32.lib")

target_include_directories(AllTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_custom_command(TARGET AllTests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/third_party/fmod/dll/fmod.dll $<TARGET_FILE_DIR:AllTests>)

add_custom_command(TARGET AllTests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:AllTests>/data/)
