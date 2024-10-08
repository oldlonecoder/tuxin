add_executable(main.app main.cc)
target_compile_features(main.app PUBLIC cxx_std_20)
target_include_directories(main.app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(main.app ${BaseTarget})

install(TARGETS ${BaseTarget} main.app
        EXPORT ${BaseTarget}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)
