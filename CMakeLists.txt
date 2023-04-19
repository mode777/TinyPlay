cmake_minimum_required(VERSION 3.6)
project(TinyRogue)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/TargetArch.cmake)
target_architecture(TARGET_ARCH)

message("Building for ${TARGET_ARCH}")

#set(CMAKE_FIND_DEBUG_MODE true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#stb libs
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb)

# Add SDL
if(WIN32)
  if(TARGET_ARCH STREQUAL "x86_32")
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/win32/x86)
  endif()
  if(TARGET_ARCH STREQUAL "x86_64")
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/win32/x64)
  endif()
  #set(SDL2_BUILDING_LIBRARY on)
endif()

find_package(SDL2 REQUIRED)

# Add Duktape
set(DUKTAPEDIR ${CMAKE_CURRENT_LIST_DIR}/thirdparty/duktape_combine)
add_library(duktape STATIC ${DUKTAPEDIR}/duktape.c thirdparty/duktape/extras/module-duktape/duk_module_duktape.c)
target_include_directories(duktape PUBLIC ${DUKTAPEDIR} thirdparty/duktape/extras/module-duktape)
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
  target_link_libraries(duktape
    m dl rt
  )
endif()

# Add executable
file(GLOB_RECURSE sources src/*.c)
file(GLOB_RECURSE headers src/*.h)

add_executable(trogue ${headers} ${sources})
target_link_libraries(trogue PRIVATE SDL2::Main duktape)

# Add tool
add_executable(img2h tools/img2h/main.c)
target_link_libraries(img2h PRIVATE stb)

# Needed by SDL for console by mingw
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
  target_link_options(trogue PRIVATE "-mconsole")
endif()

# On windows copy dlls to bin dir
if(WIN32)
  configure_file(${SDL2_INCLUDE_DIRS}/../../bin/SDL2.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SDL2.dll COPYONLY)
endif()