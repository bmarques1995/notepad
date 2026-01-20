trace_dependency(NAME Qt6 6.10 COMPONENTS Core Widgets INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qtbase.cmake.json" WORKING_DIR "${FETCHERS_LOCATION}")
trace_dependency(NAME Qt6 6.10 COMPONENTS LinguistTools INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qttools.cmake.json" WORKING_DIR "${FETCHERS_LOCATION}")
trace_dependency(NAME Qt6 6.10 COMPONENTS Svg INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qtsvg.cmake.json" WORKING_DIR "${FETCHERS_LOCATION}")

file(GLOB_RECURSE NOTEPAD_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE NOTEPAD_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE NOTEPAD_UIS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "ui/*.ui")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(PACKAGE_NAME Notepad)
add_executable(${PACKAGE_NAME} ${NOTEPAD_SRCS} ${NOTEPAD_HDRS} ${NOTEPAD_UIS})
target_compile_definitions(${PACKAGE_NAME} PUBLIC WIN32_LEAN_AND_MEAN)
set_target_properties(${PACKAGE_NAME} PROPERTIES
    AUTOUIC_SEARCH_PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

set_cxx_project_standards(${PACKAGE_NAME} 20 FALSE)


if(WIN32)
    set_target_properties(${PACKAGE_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
	target_link_options(${PACKAGE_NAME} PRIVATE "/ENTRY:mainCRTStartup")
endif()

target_link_libraries(${PACKAGE_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
)
