include(LibFindMacros)
#libfind_package(Direct3D11)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	if(CMAKE_CL_64)
		set (Direct3D11_ARCHITECTURE x64)
	else()
		set (Direct3D11_ARCHITECTURE x86)
	endif()

	if(DEFINED MSVC_VERSION AND NOT ${MSVC_VERSION} LESS 1700)
		find_path (WIN8_SDK_ROOT_DIR
			Include/um/windows.h
			PATHS
				"$ENV{ProgramFiles}/Windows Kits/8.0"
				"$ENV{ProgramFiles(x86)}/Windows Kits/8.0"
				DOC "Windows 8 SDK root directory"
		)

		if(WIN8_SDK_ROOT_DIR)
			set (Direct3D11_INC_SEARCH_PATH "${WIN8_SDK_ROOT_DIR}/Include/um" "${WIN8_SDK_ROOT_DIR}/Include/shared")
			set (Direct3D11_LIB_SEARCH_PATH "${WIN8_SDK_ROOT_DIR}/Lib/Win8/um/${Direct3D11_ARCHITECTURE}")
			set (Direct3D11_BIN_SEARCH_PATH "${WIN8_SDK_ROOT_DIR}/bin/${Direct3D11_ARCHITECTURE}")
		endif ()
	endif ()
	
	

	find_path( Direct3D11_INCLUDE_DIR 
		NAMES d3d11.h
		HINTS ${Direct3D11_INC_SEARCH_PATH}
		DOC "Direct3D11 Headers"
		)
		
    find_library( Direct3D11_DXGUID_LIBRARY 
		NAMES dxguid 
		HINTS ${Direct3D11_LIB_SEARCH_PATH}
		DOC "Direct3D11 DXGUID library"
		)
    find_library( Direct3D11_DXGI_LIBRARY 
		NAMES dxgi
		HINTS ${Direct3D11_LIB_SEARCH_PATH}
		DOC "Direct3D11 DXGI libraries"
		)
    find_library( Direct3D11_D3DCompiler_LIBRARY 
		NAMES d3dcompiler 
		HINTS ${Direct3D11_LIB_SEARCH_PATH}
		DOC "Direct3D11 D3DCompiler library"
		)
    find_library( Direct3D11_D3D11_LIBRARY 
		NAMES d3d11 
		HINTS ${Direct3D11_LIB_SEARCH_PATH}
		DOC "Direct3D11 library"
		)

endif ()

set(Direct3D11_PROCESS_INCLUDES Direct3D11_INCLUDE_DIR)
set(Direct3D11_PROCESS_LIBS Direct3D11_DXGUID_LIBRARY Direct3D11_DXGI_LIBRARY Direct3D11_D3DCompiler_LIBRARY Direct3D11_D3D11_LIBRARY )
libfind_process(Direct3D11)



