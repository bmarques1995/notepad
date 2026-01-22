trace_dependency(NAME Qt6 6.10 COMPONENTS Core Widgets INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qtbase.cmake.json" WORKING_DIR "${FETCHERS_LOCATION}")
trace_dependency(NAME Qt6 6.10 COMPONENTS LinguistTools INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qttools.cmake.json" WORKING_DIR "${FETCHERS_LOCATION}")
trace_dependency(NAME Qt6 6.10 COMPONENTS Svg INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qtsvg.cmake.json" WORKING_DIR "${FETCHERS_LOCATION}")

find_program(QT_RCC rcc REQUIRED)
find_program(QT_LRELEASE lrelease REQUIRED)

file(GLOB_RECURSE NOTEPAD_RSCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "resources/*.qrc")
file(GLOB_RECURSE NOTEPAD_LNGS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "resources/*.ts.xml")

foreach(RSC_FILE ${NOTEPAD_RSCS})
    message(STATUS "Processing ${RSC_FILE}")
	execute_process(
		COMMAND ${QT_RCC} ${CMAKE_CURRENT_SOURCE_DIR}/${RSC_FILE} -g cpp -o ${CMAKE_CURRENT_SOURCE_DIR}/${RSC_FILE}.cpp
		COMMAND_ERROR_IS_FATAL ANY
	)
endforeach()

foreach(LNG_FILE ${NOTEPAD_LNGS})
	get_filename_component(LNG_NAME "${LNG_FILE}" NAME_WE)        
	get_filename_component(LNG_DIR  "${LNG_FILE}" DIRECTORY) 
    message(STATUS "Processing ${LNG_FILE}")
	execute_process(
		COMMAND ${QT_LRELEASE} ${CMAKE_CURRENT_SOURCE_DIR}/${LNG_FILE} -qm ${CMAKE_CURRENT_SOURCE_DIR}/${LNG_DIR}/${LNG_NAME}.qm
		COMMAND_ERROR_IS_FATAL ANY
	)
endforeach()

file(GLOB_RECURSE NOTEPAD_RSCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "resources/*.cpp")
file(GLOB_RECURSE NOTEPAD_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE NOTEPAD_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE NOTEPAD_UIS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "ui/*.ui")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(PACKAGE_NAME Notepad)
add_executable(${PACKAGE_NAME} ${NOTEPAD_SRCS} ${NOTEPAD_HDRS} ${NOTEPAD_UIS} ${NOTEPAD_RSCS})
target_compile_definitions(${PACKAGE_NAME} PUBLIC WIN32_LEAN_AND_MEAN)
set_target_properties(${PACKAGE_NAME} PROPERTIES
    AUTOUIC_SEARCH_PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

set_cxx_project_standards(${PACKAGE_NAME} 20 FALSE)

add_custom_target(copy_lang_assets ALL
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${CMAKE_CURRENT_SOURCE_DIR}/resources/translations"
			${CMAKE_PREFIX_PATH}/bin/translations
			COMMENT "Copying D3D12Core dll into binary directory")
add_dependencies(${PACKAGE_NAME} copy_lang_assets)

if(WIN32)
    set_target_properties(${PACKAGE_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
	target_link_options(${PACKAGE_NAME} PRIVATE "/ENTRY:mainCRTStartup")
endif()

target_link_libraries(${PACKAGE_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
)
