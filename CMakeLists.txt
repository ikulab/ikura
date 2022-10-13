cmake_minimum_required(VERSION 3.16)
project(
	ikura
	VERSION 0.1.0
	LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(
	-std=c++17 -fdiagnostics-color=always -g
)

option(USE_CLANG "set CXX compiler to Clang" TRUE)

if(USE_CLANG)
	set(CMAKE_CXX_COMPILER clang++)
	set(CMAKE_C_COMPILER clang)
	add_compile_options(
		-Wno-nullability-completeness
	)
else()
	set(CMAKE_CXX_COMPILER gcc)
	set(CMAKE_C_COMPILER gcc)
endif()

if("${BUILD_TYPE}" STREQUAL "Release")
	add_compile_options(-DNODEBUG)
endif()

# external libraries ----------
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(./includes/imgui)
add_subdirectory(./includes/tinyfiledialogs)
add_subdirectory(./includes/easylogging++)
add_subdirectory(./includes/vk_mem_alloc)

# shader compile ----------
add_custom_target(
	shaders
	make -f compile_shaders.makefile
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
	DEPENDS ./shaders/shader.frag ./shaders/shader.vert
	COMMENT "compiling shaders"
)

# ikura lib ----------
add_subdirectory(./src)

# ikura dependencies
target_link_libraries(ikura INTERFACE vulkan glfw easyloggingpp vk_mem_alloc imgui tinyfiledialogs ${CMAKE_DL_LIBS})

# install ----------
set(ikura_install_targets
	ikura window nativeWindow virtualWindow
	appEngine renderEngine renderComponent shape
	initVulkanHppDispatchLoader
	easyloggingpp vk_mem_alloc imgui tinyfiledialogs
)

install(TARGETS ${ikura_install_targets}
	EXPORT ikuraTargets)

install(EXPORT ikuraTargets
	FILE ikuraTargets.cmake
	DESTINATION lib/cmake/ikura
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/ikuraConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/ikura"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/ikuraConfigVersion.cmake"
	VERSION "0.1.0"
	COMPATIBILITY AnyNewerVersion)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/ikuraConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/ikuraConfigVersion.cmake
	DESTINATION lib/cmake/ikura)