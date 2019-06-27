# Detect platform and set platform name
macro(detect_platform_name PLATFORM_NAME)
    if(${UNIX})
        if(${APPLE})
            if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
                set(PLATFORM_NAME "osx")
            endif()
        else()
            set(PLATFORM_NAME "linux")
        endif()
    elseif(${WIN32})
        set(PLATFORM_NAME "windows")
    endif()
endmacro(detect_platform_name)

# Make absolute path to source files
macro(set_sources SOURCE_OUTPUT)
    foreach(ARG ${ARGN})
        list(APPEND ${SOURCE_OUTPUT} "${CMAKE_CURRENT_LIST_DIR}/${ARG}")
    endforeach(ARG)
endmacro(set_sources)

# Make install target for files
macro(make_install_files_target PREFIX)
    foreach(ARG ${ARGN})
        get_filename_component(DIR ${ARG} DIRECTORY)
        string(REGEX REPLACE "^${CMAKE_CURRENT_LIST_DIR}" "" DIR ${DIR})
        install(FILES ${ARG} DESTINATION "${PREFIX}/${DIR}")
    endforeach(ARG)
endmacro(make_install_files_target)
