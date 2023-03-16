cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME Battle_City)
project (${PROJECT_NAME})


add_executable(${PROJECT_NAME} 
	source/main.cpp
	source/Resources/Resource_Manager.cpp
	source/Resources/Resource_Manager.h
	source/Resources/stb_image.h

	source/Renderer/Shader_Program.cpp
	source/Renderer/Shader_Program.h
	source/Renderer/Texture2D.cpp
	source/Renderer/Texture2D.h
	source/Renderer/Sprite.cpp
	source/Renderer/Sprite.h
	source/Renderer/Vertex_Buffer.h
	source/Renderer/Vertex_Buffer.cpp
	source/Renderer/Vertex_Array.h
	source/Renderer/Vertex_Array.cpp
	source/Renderer/Index_Buffer.h
	source/Renderer/Index_Buffer.cpp
	source/Renderer/Vertex_Buffer_Layout.cpp
	source/Renderer/Vertex_Buffer_Layout.h
	source/Renderer/Renderer.cpp
	source/Renderer/Renderer.h
	source/Renderer/Sprite_Animator.cpp
	source/Renderer/Sprite_Animator.h

	source/Game/Game.cpp
	source/Game/Game.h
	source/Game/Level.cpp
	source/Game/Level.h

	source/Game/GameObjects/Player_Tank.cpp
	source/Game/GameObjects/Player_Tank.h
	source/Game/GameObjects/Game_Object.cpp
	source/Game/GameObjects/Game_Object.h
	source/Game/GameObjects/Brick_Wall.cpp
	source/Game/GameObjects/Brick_Wall.h
	source/Game/GameObjects/Beton_Wall.cpp
	source/Game/GameObjects/Beton_Wall.h
	source/Game/GameObjects/Trees.cpp
	source/Game/GameObjects/Trees.h
	source/Game/GameObjects/Ice.cpp
	source/Game/GameObjects/Ice.h
	source/Game/GameObjects/Water.cpp
	source/Game/GameObjects/Water.h
	source/Game/GameObjects/Eagle.cpp
	source/Game/GameObjects/Eagle.h
	source/Game/GameObjects/Border.cpp
	source/Game/GameObjects/Border.h


	source/System/Timer.cpp
	source/System/Timer.h
)


target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALLL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME}  glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)