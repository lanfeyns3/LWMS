cmake_minimum_required(VERSION 3.19.1)

# You are allowed to change the following two variables below
set(BUILD_EXAMPLE N CACHE STRING "Enable example build")
set(DEMO Y)
set(DEV Y)

message(STATUS ${BUILD_EXAMPLE})
# -----------------------------------------------------------

set(m_PRJ_EXISTS N)
set(m_systemBuilt BUILT_PROJECT_${CMAKE_HOST_SYSTEM_NAME})
message(STATUS ${CMAKE_HOST_SYSTEM_NAME})

if (DEFINED CACHE{${m_systemBuilt}})
    set(m_PRJ_EXISTS Y)
endif()

if (NOT ${m_PRJ_EXISTS} OR ${DEV})
    if (DEMO STREQUAL "Y")
        message(STATUS "Building demo project")
            project("windowsManager" C)
            
            find_package(X11 REQUIRED)
            
            add_executable(windowsManager 
                "src/demo.c"
                "src/window.h"
                "src/window.c"
                "src/backends/x11window.h"
                "src/backends/x11window.c"
            )
            target_link_libraries(windowsManager ${X11_LIBRARIES})
            target_include_directories(windowsManager PUBLIC ${X11_INCLUDE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/vendor)
            set(BUILT_PROJECT_${CMAKE_HOST_SYSTEM_NAME} CACHE STRING "Internal Variable")
    else()
        message("Building just library")
    endif()
else()
    message(STATUS "Already built")
endif()

if (BUILD_EXAMPLE)
    message(STATUS "Building an example")
    string(TOLOWER "${BUILD_EXAMPLE}" M_EXAMPLE_PROJECT)
    message(STATUS "Example name: " ${M_EXAMPLE_PROJECT})
    set(EXAMPLE_DIR ${CMAKE_SOURCE_DIR}/examples/${M_EXAMPLE_PROJECT}/)
    message(STATUS ${EXAMPLE_DIR})
    if (IS_DIRECTORY "${EXAMPLE_DIR}")
        add_subdirectory(${EXAMPLE_DIR})
    else()
        message(FATAL_ERROR ${EXAMPLE_DIR} "\n ^^^^^^^^^^^^^^^^^^^^^^ \n The directory is not a real example")
    endif()
else()
endif()
