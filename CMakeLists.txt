project(Assignment_1)
cmake_minimum_required (VERSION 3.0)
aux_source_directory(src SRC_LIST)
find_package(OpenGL REQUIRED)

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)
set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw GLEW
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(Jetpack_Joyride ${SRC_LIST}
lib/shader.cpp
lib/shader.hpp
lib/text2D.hpp
lib/text2D.cpp
lib/texture.cpp
lib/texture.hpp
)
target_link_libraries(Jetpack_Joyride ${ALL_LIBS})
