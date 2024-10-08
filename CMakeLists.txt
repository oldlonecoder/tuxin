cmake_minimum_required(VERSION 3.13..3.29 FATAL_ERROR)
project(tuxin VERSION 0.1.0 LANGUAGES CXX)
set(BaseTarget ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

message("Entering ${PROJECT_NAME} project configuration:")
include(GNUInstallDirs)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${BaseTarget} STATIC  #SHARED
            include/${BaseTarget}/exports
            include/${BaseTarget}/tools/colors.h src/tools/colors.cc
            include/${BaseTarget}/tools/glyphes.h src/tools/glyphes.cc
            include/${BaseTarget}/tools/cadres.h src/tools/cadres.cc
            include/${BaseTarget}/tools/string.h src/tools/string.cc
            include/${BaseTarget}/tools/geometry.h src/tools/geometry.cc
            include/${BaseTarget}/tools/book.h src/tools/book.cc
            include/${BaseTarget}/tools/cmdargs.h src/tools/cmdargs.cc
            include/${BaseTarget}/tools/sscan.h src/tools/sscan.cc
            include/${BaseTarget}/tools/object.h src/tools/object.cc
            include/${BaseTarget}/tools/signals.h
            include/${BaseTarget}/tui/globals.h src/tui/globals.cc
            include/${BaseTarget}/tui/twindc.h src/tui/twindc.cc src/tui/twindc.chr.cc
            include/${BaseTarget}/tui/terminal.h src/tui/terminal.cc
            include/${BaseTarget}/tui/element.h src/tui/element.cc src/tui/element.painter.cc
            include/${BaseTarget}/tui/events.h src/tui/events.cc
            include/${BaseTarget}/tui/application.h src/tui/application.cc
            include/${BaseTarget}/tui/input_track.h src/tui/input_track.cc
            include/${BaseTarget}/tui/window.h src/tui/window.cc
            include/${BaseTarget}/tui/desktop.h src/tui/desktop.cc
            include/${BaseTarget}/tui/ansi.h  src/tui/ansi.cc
            include/tuxin/tui/statusbar.h src/tui/statusbar.cc


            # include/${BaseTarget}/lexer/lexer_types.h cc/lexer/lexer_types.cc
            # include/${BaseTarget}/lexer/token_data.h cc/lexer/token_data.cc
            # include/${BaseTarget}/lexer/tokens_table.h cc/lexer/tokens_table.cc
            # include/${BaseTarget}/lexer/lexer.h cc/lexer/lexer.cc
            # include/${BaseTarget}/est/alu.h cc/est/alu.cc
            # include/${BaseTarget}/est/node.h cc/est/node.cc
            # include/${BaseTarget}/est/variable.h cc/est/variable.cc
            # include/${BaseTarget}/est/bloc.h cc/est/bloc.cc
            # include/${BaseTarget}/est/expression.h cc/est/expression.cc


            # include/${BaseTarget}/elements/element.h  cc/intui/elements/element.cc


            # include/intui/elements/screen.h cc/intui/elements/screen.cc

)

target_compile_definitions(${BaseTarget} PUBLIC "${BaseTarget}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${BaseTarget} EXPORT_FILE_NAME ${${BaseTarget}_export})

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()

target_include_directories(${BaseTarget} PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           $<INSTALL_INTERFACE:include>
)

target_link_libraries(${BaseTarget} ${CMAKE_DL_LIBS}) # and other system dependencies...








install(DIRECTORY
        include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)


add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
    install_manifest.txt to be uninstalled!
)
# Enable packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME ${BaseTarget})
set(CPACK_GENERATOR "TGZ")

# Include CPack
#include(CPack) # Scrap!! No way to include header files!

add_subdirectory(tddv)
