#--------------------------------------------------------------------------
# lab3 project
#--------------------------------------------------------------------------

PROJECT(lab6)
FILE(GLOB lab6_headers code/*.h *.jpg *.obj)
FILE(GLOB lab6_sources code/*.cc resources/*.vs resources/*.fs )

SET(files_lab6 ${lab6_headers} ${lab6_sources})
SOURCE_GROUP("lab6" FILES ${files_lab6})

ADD_EXECUTABLE(lab6 ${files_lab6})
TARGET_LINK_LIBRARIES(lab6 core render glm)
ADD_DEPENDENCIES(lab6 core render glm)
add_custom_command(
    TARGET lab6 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    ${CMAKE_SOURCE_DIR}/bin/resources/
)

set_target_properties(lab6 PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)