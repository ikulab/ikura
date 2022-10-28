set(common_include_dir
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/includes>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/includes/easylogging++>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/includes/vk_mem_alloc>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/includes/shaderc>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/includes/libshaderc_util>
$<INSTALL_INTERFACE:include/ikura>
$<INSTALL_INTERFACE:include/ikura/easylogging++>
$<INSTALL_INTERFACE:include/ikura/vk_mem_alloc>
$<INSTALL_INTERFACE:include/ikura/shaderc>
$<INSTALL_INTERFACE:include/ikura/libshaderc_util>
)

add_library(ikura STATIC init.cpp)
target_link_directories(ikura PUBLIC "${common_include_dir}")

add_subdirectory(./common)
target_include_directories(ikura-common PUBLIC "${common_include_dir}")
target_link_libraries(ikura PUBLIC ikura-common)

add_subdirectory(./window)
target_include_directories(ikura-nativeWindow PUBLIC "${common_include_dir}")
target_include_directories(ikura-virtualWindow PUBLIC "${common_include_dir}")
target_include_directories(ikura-window PUBLIC "${common_include_dir}")
target_link_libraries(ikura PUBLIC ikura-nativeWindow ikura-virtualWindow)

add_subdirectory(./engine)
target_include_directories(ikura-appEngine PUBLIC "${common_include_dir}")
target_include_directories(ikura-renderEngine PUBLIC "${common_include_dir}")
target_link_libraries(ikura PUBLIC ikura-appEngine ikura-renderEngine)

add_subdirectory(./renderComponent)
target_include_directories(ikura-renderComponent PUBLIC "${common_include_dir}")
target_link_libraries(ikura PUBLIC ikura-renderComponent)

add_subdirectory(./misc)
target_include_directories(ikura-misc PUBLIC "${common_include_dir}")
target_link_libraries(ikura PUBLIC ikura-misc)

add_subdirectory(./shape)
target_include_directories(ikura-shape PUBLIC "${common_include_dir}")
target_link_libraries(ikura PUBLIC ikura-shape)

target_include_directories(ikura INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:include/ikura>
	$<INSTALL_INTERFACE:${common_include_dir}>)

install(FILES ${CMAKE_BINARY_DIR}/src/ikuraConfig.h init.hpp
	DESTINATION include/ikura)