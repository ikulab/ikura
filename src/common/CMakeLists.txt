add_library(ikura-common STATIC ./resourceDirectory.cpp)

install(FILES
	${CMAKE_SOURCE_DIR}/src/common/renderPrimitiveTypes.hpp
	${CMAKE_SOURCE_DIR}/src/common/uniformBufferInfo.hpp
	DESTINATION include/ikura/common)