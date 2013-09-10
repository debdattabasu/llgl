find_package(Direct3D11 REQUIRED)

include_directories(${Direct3D11_INCLUDE_DIRS} 
	${Llgl_SOURCE_DIR}
	)
	
file(GLOB LlglDriverDirect3D11_SRC
    "*.cpp"
	"*.h"
	)
add_definitions(-DLLGL_EXPORT)
	
#add_library(LlglDriverDirect3D11 SHARED ${LlglDriverDirect3D11_SRC})
#target_link_libraries(LlglDriverDirect3D11 ${Direct3D11_LIBRARIES} LlglCommon)
#if(NOT MSVC_IDE)
#	cotire(LlglDriverDirect3D11)
#endif()
