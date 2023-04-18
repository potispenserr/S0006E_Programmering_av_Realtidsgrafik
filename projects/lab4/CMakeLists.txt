#--------------------------------------------------------------------------
# lab3 project
#--------------------------------------------------------------------------

PROJECT(lab4)
FILE(GLOB lab4_headers code/*.h *.jpg )
FILE(GLOB lab4_sources code/*.cc resources/*.vs resources/*.fs)

SET(files_lab4 ${lab4_headers} ${lab4_sources})
SOURCE_GROUP("lab4" FILES ${files_lab4})

ADD_EXECUTABLE(lab4 ${files_lab4})
TARGET_LINK_LIBRARIES(lab4 core render glm)
ADD_DEPENDENCIES(lab4 core render glm)
add_custom_command(
    TARGET lab4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    ${CMAKE_SOURCE_DIR}/bin/resources/
)

set_target_properties(lab4 PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)