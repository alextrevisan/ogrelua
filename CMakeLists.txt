cmake_minimum_required (VERSION 2.8)

project (orelua)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/;${CMAKE_MODULE_PATH}")

add_library(ogrelua SHARED main.cpp
                       KeyListener.cpp
                       InputManager.cpp
                       FrameListener.cpp)

include_directories(LuaIntf)

##############################################################
#  Find Lua
##############################################################
find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

##############################################################
#  Find Ogre
##############################################################
find_package(OGRE REQUIRED)



if(NOT ((${OGRE_VERSION} VERSION_EQUAL "1.8.0") OR (${OGRE_VERSION} VERSION_GREATER "1.8.0")))
    message(SEND_ERROR "You need Ogre 1.8.0 or later to build this. You can get it from sinbad's repository here: https://bitbucket.org/sinbad/ogre")
endif()

include_directories(${OGRE_INCLUDE_DIRS})

##############################################################
#  Find OIS
##############################################################
find_package(OIS REQUIRED)

if(NOT OIS_FOUND)
        message(SEND_ERROR "Failed to find OIS.")
endif()

include_directories(${OIS_INCLUDE_DIRS})

target_link_libraries(ogrelua ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LUA_LIBRARIES})

set_target_properties(ogrelua PROPERTIES PREFIX "")

add_definitions(-std=c++11)
