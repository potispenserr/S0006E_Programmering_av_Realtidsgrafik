#--------------------------------------------------------------------------
# lab3 project
#--------------------------------------------------------------------------

PROJECT(lab3)
FILE(GLOB lab3_headers code/*.h *.jpg *.hpp)
FILE(GLOB lab3_sources code/*.cc)

SET(files_lab3 ${lab3_headers} ${lab3_sources})
SOURCE_GROUP("lab3" FILES ${files_lab3})

ADD_EXECUTABLE(lab3 ${files_lab3})
TARGET_LINK_LIBRARIES(lab3 core render glm)
ADD_DEPENDENCIES(lab3 core render glm)
add_custom_command(
    TARGET lab3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    ${CMAKE_SOURCE_DIR}/bin/resources/
)

set_target_properties(lab3 PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)