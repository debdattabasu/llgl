#pragma once
#include <stdint.h>
#include <exception>
#include <string>
#include <memory>
#include <vector>
#include <mutex>


#pragma warning(disable : 4251)

#define LLGL_NAMESPACE(ns) namespace ns { 
#define LLGL_NAMESPACE2(ns1, ns2) namespace ns1 {  namespace ns2 {

#define LLGL_NAMESPACE_END } 
#define LLGL_NAMESPACE_END2 }}

#define LLGL_ENUM(enumName) enum class enumName 
#define LLGL_ENUM_OPERATORS(enumName)inline enumName operator | (enumName lhs, enumName rhs)\
		{\
		    return (enumName)((int)lhs | (int)rhs);\
		}\
		inline enumName& operator |= (enumName& lhs, enumName rhs)\
		{\
		    lhs = (enumName)((int)lhs | (int)rhs);\
		    return lhs;\
		}\
		inline enumName operator & (enumName lhs, enumName rhs)\
		{\
		    return (enumName)((int)lhs & (int)rhs);\
		}\
		inline enumName& operator &= (enumName& lhs, enumName rhs)\
		{\
		    lhs = (enumName)((int)lhs & (int)rhs);\
		    return lhs;\
		}\


#ifndef LLGL_STATIC
	#ifdef LLGL_EXPORT
		#define LLGL_CLASS(className) class _declspec(dllexport) className; \
			typedef std::shared_ptr<className> className##Ptr; \
			typedef std::weak_ptr<className> className##WeakPtr; \
			class _declspec(dllexport) className 
	#else
		#define LLGL_CLASS(className) class _declspec(dllimport) className; \
			typedef std::shared_ptr<className> className##Ptr; \
			typedef std::weak_ptr<className> className##WeakPtr; \
			class _declspec(dllimport) className 
	#endif
#else
	#define LLGL_CLASS(className) class className; \
		typedef std::shared_ptr<className> className##Ptr; \
		typedef std::weak_ptr<className> className##WeakPtr; \
		class className 
#endif

#ifndef max
	#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(NonCopyable);
LLGL_CLASS(Exception);
LLGL_CLASS(Driver);
LLGL_CLASS(Context);
LLGL_CLASS(ContextChild);
LLGL_CLASS(Capabilities);
LLGL_ENUM(FormatType);
LLGL_ENUM(FormatUsage);
LLGL_CLASS(Format);
LLGL_CLASS(Resource);
LLGL_CLASS(ResourceView);
LLGL_CLASS(BufferView);
LLGL_CLASS(BufferShaderResourceView);
LLGL_CLASS(BufferUnorderedAccessView);
LLGL_CLASS(BufferVertexArrayView);
LLGL_CLASS(BufferIndexArrayView);
LLGL_CLASS(BufferDataAccessView);
LLGL_CLASS(Buffer);
LLGL_CLASS(Texture1DView);
LLGL_CLASS(Texture1DDataAccessView);
LLGL_CLASS(Texture1DShaderResourceView);
LLGL_CLASS(Texture1DUnorderedAccessView);
LLGL_CLASS(Texture2DView);
LLGL_CLASS(Texture2DShaderResourceView);
LLGL_CLASS(Texture2DUnorderedAccessView);
LLGL_CLASS(Texture2DRenderTargetView);
LLGL_CLASS(Texture2DDepthStencilView);
LLGL_CLASS(Texture2DDataAccessView);
LLGL_CLASS(Texture3DView);
LLGL_CLASS(Texture3DDataAccessView);
LLGL_CLASS(Texture3DShaderResourceView);
LLGL_CLASS(Texture3DUnorderedAccessView);
LLGL_CLASS(Texture1D);
LLGL_CLASS(Texture2D);
LLGL_CLASS(Texture3D);


LLGL_NAMESPACE_END;