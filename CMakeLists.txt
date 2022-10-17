cmake_minimum_required(VERSION 3.16)
project(
	ikura
	VERSION 0.1.0
	LANGUAGES C CXX
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

set(ikura-ext-src "")
add_subdirectory(./includes/imgui)
add_subdirectory(./includes/easylogging++)
add_subdirectory(./includes/vk_mem_alloc)

add_library(ikura-ext-lib STATIC ${ikura-ext-src})
target_compile_definitions(ikura-ext-lib PUBLIC AUTO_INITIALIZE_EASYLOGGINGPP)

# shader compile ----------
add_custom_target(
	shaders
	make -f compile_shaders.makefile
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts
	DEPENDS ${CMAKE_SOURCE_DIR}/shaders/shader.frag ${CMAKE_SOURCE_DIR}/shaders/shader.vert
	COMMENT "compiling shaders"
)

# ikura lib ----------
add_subdirectory(./src)
add_dependencies(ikura shaders)

# ikura dependencies
target_link_libraries(ikura INTERFACE vulkan glfw ${CMAKE_DL_LIBS})
target_link_libraries(ikura INTERFACE ikura-ext-lib)

# install ----------
set(ikura_install_targets
	ikura window nativeWindow virtualWindow
	appEngine renderEngine renderComponent shape
	initVulkanHppDispatchLoader
	ikura-ext-lib
)

add_custom_target(ikura-pack ALL
	COMMAND ${CMAKE_SOURCE_DIR}/scripts/pack_library.sh
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	DEPENDS ${ikura_install_targets}
	COMMENT "packing ikura.a")

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

# header file
install(FILES ${CMAKE_SOURCE_DIR}/src/ikura.hpp
	DESTINATION include/ikura)