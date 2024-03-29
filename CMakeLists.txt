cmake_minimum_required(VERSION 3.11)
# Require modern C++
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

#### Add External Dependencies ####
#add_subdirectory("lib/sfml")
#set(SFML_INCS "lib/sfml/include")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
#add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
#  -E copy_directory
#    "${PROJECT_SOURCE_DIR}/res"
#    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
#)

# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

## B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
#### Lib Enging
file(GLOB_RECURSE SOURCE_FILES lib_engine/*.cpp lib_engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/lib_engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## ECM Lib ##
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)
set_target_properties(PRACTICAL_1 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_1 copy_resources)

#### practical_2 ####
file(GLOB_RECURSE SOURCES 2_invaders/*.cpp 2_invaders/*.h)
add_executable(2_INVADERS ${SOURCES} )
target_include_directories(2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(2_INVADERS sfml-graphics)
set_target_properties(2_INVADERS 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(2_INVADERS copy_resources)

#### 4_tile_engine ####
file(GLOB_RECURSE SOURCES 4_tile_engine/*.cpp 4_tile_engine/*.h)
add_executable(4_TILE_ENGINE ${SOURCES} )
target_include_directories(4_TILE_ENGINE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(4_TILE_ENGINE lib_maths lib_tile_level_loader sfml-graphics)
set_target_properties(4_TILE_ENGINE 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(4_TILE_ENGINE copy_resources)

#### 5_pacman ####
file(GLOB_RECURSE SOURCES 5_pacman/*.cpp 5_pacman/*.h)
add_executable(5_PACMAN ${SOURCES})
target_include_directories(5_PACMAN SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(5_PACMAN lib_ecm lib_maths lib_tile_level_loader sfml-graphics)
set_target_properties(5_PACMAN 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(5_PACMAN copy_resources)

#### 6_physics ####
## physics
file(GLOB_RECURSE SOURCES 6_physics/*.cpp 6_physics/*.h)
add_executable(6_PHYSICS ${SOURCES})
target_include_directories(6_PHYSICS SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(6_PHYSICS Box2D sfml-graphics)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_6_PHYSICS)

#### 7_platformer ####
file(GLOB_RECURSE SOURCES 7_platformer/*.cpp 7_platformer/*.h)
file(GLOB_RECURSE CMPNTS 7_platformer/components/*.cpp 7_platformer/components/*.h)
file(GLOB_RECURSE SCENES 7_platformer/scenes/*.cpp 7_platformer/scenes/*.h)
add_executable(7_PLATFORMER ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
#target_include_directories(7_PLATFORMER SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(7_PLATFORMER lib_engine)
set(EXECUTABLES ${EXECUTABLES} 7_PLATFORMER)

add_dependencies(7_PLATFORMER copy_resources)

set_target_properties(7_PLATFORMER 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

## Steering
file(GLOB_RECURSE SOURCES 8_steering/*.cpp 8_steering/*.h)
file(GLOB_RECURSE CMPNTS 8_steering/components/*.cpp 8_steering/components/*.h)
file(GLOB_RECURSE PF_CMPNTS 8_steering/pf_components/*.cpp 8_steering/pf_components/*.h)
file(GLOB_RECURSE SCENES 8_steering/scenes/*.cpp 8_steering/scenes/*.h)
add_executable(8_STEERING ${SOURCES} ${CMPNTS} ${SCENES} ${PF_CMPNTS})
source_group("components" FILES ${CMPNTS})
source_group("pf_components" FILES ${PF_CMPNTS})
target_link_libraries(8_STEERING lib_engine)
set(EXECUTABLES ${EXECUTABLES} 8_STEERING)

set_target_properties(8_STEERING 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

add_dependencies(8_STEERING copy_resources)

## Decisions
file(GLOB_RECURSE SOURCES 9_decisions/*.cpp 9_decisions/*.h)
file(GLOB_RECURSE CMPNTS 9_decisions/components/*.cpp 9_decisions/components/*.h)
file(GLOB_RECURSE SCENES 9_decisions/scenes/*.cpp 9_decisions/scenes/*.h)
add_executable(9_DECISIONS ${SOURCES} ${CMPNTS} ${SCENES})
source_group("components" FILES ${CMPNTS})
source_group("scenes" FILES ${SCENES}})
target_link_libraries(9_DECISIONS lib_engine)
set(EXECUTABLES ${EXECUTABLES} 9_DECISIONS)
set_target_properties(9_DECISIONS 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(9_DECISIONS copy_resources)

#file(GLOB_RECURSE SOURCES 8_steering/*.cpp 8_steering/*.h)
#file(GLOB_RECURSE CMPNTS 8_steering/components/*.cpp 8_steering/components/*.h)
#file(GLOB_RECURSE SCENES 8_steering/scenes/*.cpp 8_steering/scenes/*.h)
#add_executable(8_STEERING ${SOURCES} ${CMPNTS} ${SCENES} ${RESOURCE_FILES})
#target_link_libraries(8_STEERING lib_engine)
#set(EXECUTABLES ${EXECUTABLES} 8_STEERING)