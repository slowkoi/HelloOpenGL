# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (HelloOpengGL)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
src/main.cpp
src/stb_image.cpp
)

# Add an executable with the above sources
add_executable(HelloOpengGL ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(HelloOpengGL
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_DIR "third-party/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(HelloOpengGL "glfw" "${GLFW_LIBRARIES}")
target_include_directories(HelloOpengGL PRIVATE "t${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

set(GLAD_DIR "third-party/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

set(GLM_DIR "third-party/glm")
include_directories("${GLM_DIR}")

set(FREETYPE_DIR "third-party/freetype")
add_subdirectory("${FREETYPE_DIR}")
target_link_libraries(HelloOpengGL "freetype" "${FREETYPE_LIBRARIES}")
target_include_directories(HelloOpengGL PRIVATE "t${FREETYPE_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "FREETYPE_INCLUDE_NONE")

# Scan through resource folder for updated files and copy if none existing or changed
file (GLOB_RECURSE resources "resources/*.*")
foreach(resource ${resources})
 get_filename_component(filename ${resource} NAME)
 get_filename_component(dir ${resource} DIRECTORY)
 get_filename_component(dirname ${dir} NAME)
 
 set (output "")
 
 while(NOT ${dirname} STREQUAL resources)
  get_filename_component(path_component ${dir} NAME)
  set (output "${path_component}/${output}")
  get_filename_component(dir ${dir} DIRECTORY)
  get_filename_component(dirname ${dir} NAME)
 endwhile()
 
 set(output "${CMAKE_CURRENT_BINARY_DIR}/resources/${output}/${filename}")
 
 add_custom_command(
  COMMENT "Moving updated resource-file '${filename}'"
  OUTPUT ${output}
  DEPENDS ${resource}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${resource}
  ${output}
 )
 add_custom_target(${filename} ALL DEPENDS ${resource} ${output})
 
endforeach()