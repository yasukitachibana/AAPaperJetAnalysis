###########################
### Initial Cmake Setup ###
###########################

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(JetAnalysis CXX C)

# Fail if cmake is called in the source directory
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message("source directory:" ${CMAKE_SOURCE_DIR})
  message("binary directory:" ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "You don't want to configure in the source directory!")
endif()

# for mac compliance
cmake_policy(SET CMP0042 NEW)

# Tell cmake where to find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmakemodules")


###############################
### Compiler & Linker Flags ###
###############################
message("Compiler and Linker flags ...")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O -fPIC -pipe -Wall -std=c++11")
## can turn off some warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -Wno-unused-variable ")
## can turn on debugging information
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

### system dependence.
### note that APPLE also defines UNIX, hence the elseif to differentiate
if (APPLE)
    message( STATUS "Apple : " ${CMAKE_HOST_SYSTEM})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang") 
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare -Wno-unused-but-set-variable -Wno-parentheses -fext-numeric-literals")
    endif()

    ## can turn off some warnings
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-private-field")
elseif(UNIX) 
    message( STATUS "Linux : " ${CMAKE_HOST_SYSTEM})
    ## can turn off some warnings
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare -Wno-unused-but-set-variable -Wno-parentheses -fext-numeric-literals")
    endif()

    ## Additional options
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()   

message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS})
#message(STATUS "LD_FLAGS = " ${CMAKE_EXE_LINKER_FLAGS})




###########################
### Required packages   ###
###########################


message("Looking for ROOT ...")
find_package(ROOT)
if (${ROOT_FOUND})
  include_directories(${ROOT_INCLUDES})
  Message(STATUS "ROOT Include dir : " ${ROOT_INCLUDES})
  Message(STATUS "ROOT Libraries : " ${ROOT_LIBRARIES})
endif()

message("Looking for Pythia8 ...")
find_package(Pythia8)
if (${PYTHIA8_FOUND})
  include_directories(${PYTHIA8_INCLUDE_DIR})
  Message(STATUS "Pythia8 Include dir : " ${PYTHIA8_INCLUDE_DIR})
endif()


add_subdirectory(fjcore)
add_subdirectory(tinyxml2)
add_subdirectory(src)

add_executable (Main ./src/main.cc)
target_link_libraries (Main main_lib fjcore_lib tinyxml2_lib ${ROOT_LIBRARIES} ${PYTHIA8_LIBRARIES})
