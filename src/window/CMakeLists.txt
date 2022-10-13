file(GLOB NATIVE_WINDOW_SRC nativeWindow/*.cpp)
file(GLOB VIRTUAL_WINDOW_SRC virtualWindow/*.cpp)

add_library(nativeWindow STATIC ${NATIVE_WINDOW_SRC})
add_library(virtualWindow STATIC ${VIRTUAL_WINDOW_SRC})
add_library(window STATIC window.cpp)

target_link_libraries(nativeWindow window)
target_link_libraries(virtualWindow window)

file(GLOB headers ./*.hpp)
install(FILES ${headers}
	DESTINATION include/ikura/window)

file(GLOB native_window_headers nativeWindow/*.hpp)
install(FILES ${native_window_headers}
	DESTINATION include/ikura/window/nativeWindow)

file(GLOB virtual_window_headers virtualWindow/*.hpp)
install(FILES ${virtual_window_headers}
	DESTINATION include/ikura/window/virtualWindow)
