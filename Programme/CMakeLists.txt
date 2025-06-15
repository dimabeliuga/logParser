
set(PROGRAM_SUBDIRS Main_Components Filters_Library Entry_Point)

foreach(subdir ${PROGRAM_SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}")
        add_subdirectory(${subdir})
        message("Subdirectory [${subdir}] has been added")
    else()  
        message("${subdir} - is not a subdirectory")
    endif()
endforeach()
