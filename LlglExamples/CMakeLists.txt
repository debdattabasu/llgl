include_directories(${Llgl_SOURCE_DIR})
file(GLOB Examples_SRC
    "*.cpp"
	"*.h"
	)
add_executable(Examples ${Examples_SRC})
target_link_libraries(Examples Llgl)

if(NOT MSVC_IDE)
	cotire(Examples)
endif()
