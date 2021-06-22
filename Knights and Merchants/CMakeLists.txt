cmake_minimum_required (VERSION 3.20)
project ("Knights and Merchants" VERSION 1.0.0.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

#######################################################################################
# Google Test
#######################################################################################

include (FetchContent)

FetchContent_Declare (
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#######################################################################################


file (GLOB_RECURSE sources LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file (GLOB_RECURSE headers LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file (GLOB_RECURSE tests LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)


add_executable (KaM-Win-x86 WIN32 ${sources} ${headers})
target_include_directories (KaM-Win-x86 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)


add_executable (KaM-Tests ${sources} ${headers} ${tests})
target_link_libraries (KaM-Tests gtest_main gmock_main)
target_include_directories (KaM-Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
