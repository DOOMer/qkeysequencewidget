cmake_minimum_required(VERSION 2.6)

# set project's name
project( demo_runtime )

find_package( Qt4 REQUIRED COMPONENTS QtCore QtGui)
include( "${QT_USE_FILE}" )

#---- build

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_definitions(-DNDEBUG)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
    add_definitions("-O2")
endif(${CMAKE_BUILD_TYPE} MATCHES "Release")
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
    # dislpay all compile warnings
    add_definitions("-Wall")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/qkeysequencewidget/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/demos/run-time/src/")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/demos/run-time/src/")

include_directories("qkeysequencewidget/src")

# run-time demo
set(DEMO_RUNTIME_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/run-time//src/main.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/run-time//src/widget.cpp)

set(DEMO_RUNTIME_HDR_MOC 
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/run-time//src/widget.h)

qt4_wrap_cpp(DEMO_RUNTIME_MOC ${DEMO_RUNTIME_HDR_MOC} )

add_executable(demo_runtime ${DEMO_RUNTIME_SRC} ${DEMO_RUNTIME_MOC} ${QKSW_QRC})
target_link_libraries(demo_runtime qkeysequencewidget ${QT_LIBRARIES})

# design-time demo
set(DEMO_DESIGNTIME_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/design-time//src/main.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/design-time//src/widget.cpp)

set(DEMO_DESIGNTIME_HDR_MOC 
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/design-time//src/widget.h)

set(DEMO_DESIGNTIME_UI  
  ${CMAKE_CURRENT_SOURCE_DIR}/demos/design-time//src/widget.ui)

qt4_wrap_cpp(DEMO_DESIGNTIME_MOC ${DEMO_DESIGNTIME_HDR_MOC} )
qt4_wrap_ui(DEMO_DESIGNTIME_SRC_UI ${DEMO_DESIGNTIME_UI} )

add_executable(demo_designtime ${DEMO_RUNTIME_SRC} ${DEMO_RUNTIME_MOC} ${QKSW_QRC} ${DEMO_DESIGNTIME_SRC_UI})
target_link_libraries(demo_designtime qkeysequencewidget ${QT_LIBRARIES})
