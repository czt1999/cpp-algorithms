# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)
foreach( sourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" name ${sourcefile} )
    add_executable( ${name} ${sourcefile} )

    set_target_properties(${name} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${name} OpenMP::OpenMP_CXX)
    endif()
    install(TARGETS ${name} DESTINATION "bin/cipher")

endforeach( sourcefile ${APP_SOURCES} )
