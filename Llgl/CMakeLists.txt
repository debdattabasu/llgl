include_directories(${Llgl_SOURCE_DIR})
file(GLOB Llgl_SRC
	"*.h"
    "*.cpp"
	)
add_definitions(-DLLGL_EXPORT)
add_library(Llgl ${LLGL_LIBRARY_TYPE}  ${Llgl_SRC})

if(NOT MSVC_IDE)
	cotire(Llgl)
endif()