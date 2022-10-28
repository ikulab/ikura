cmake_minimum_required(VERSION 3.16)
project(
	ikura
	VERSION 1.0.0
	LANGUAGES C CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(
	-std=c++17 -fdiagnostics-color=always -g)

configure_file(${PROJECT_SOURCE_DIR}/src/ikura/ikuraConfig.h.in
	${PROJECT_SOURCE_DIR}/src/ikura/ikuraConfig.h)

# Clang setting ----------
option(USE_CLANG "set CXX compiler to Clang" TRUE)

# Release / Debug ----------
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
add_subdirectory(./includes/shaderc)
add_subdirectory(./includes/libshaderc_util)

add_library(ikura-ext-lib STATIC ${ikura-ext-src})
target_compile_definitions(ikura-ext-lib PUBLIC AUTO_INITIALIZE_EASYLOGGINGPP)

# ikura lib ----------
add_subdirectory(./src/ikura)

# link external static library files
target_link_libraries(ikura
	PUBLIC ${PROJECT_SOURCE_DIR}/libs/libshaderc_combined.a)

# ikura dependencies
target_link_libraries(ikura INTERFACE vulkan glfw ${CMAKE_DL_LIBS})
target_link_libraries(ikura INTERFACE ikura-ext-lib)

# install ----------
set(ikura_install_targets
	ikura ikura-window ikura-nativeWindow ikura-virtualWindow
	ikura-appEngine ikura-renderEngine ikura-renderComponent
	ikura-shape ikura-common ikura-misc ikura-ext-lib
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
	VERSION CMAKE_PROJECT_VERSION
	COMPATIBILITY AnyNewerVersion)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/ikuraConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/ikuraConfigVersion.cmake
	DESTINATION lib/cmake/ikura)

# header file
install(FILES ${PROJECT_SOURCE_DIR}/src/ikura.hpp
	DESTINATION include/ikura)