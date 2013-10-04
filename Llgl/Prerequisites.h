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
		#define LLGL_EXCEPTION_DECLARE(exceptionClassName) \
			class _declspec(dllexport) exceptionClassName##Exception : public Llgl::Exception\
			{\
			public:\
				exceptionClassName##Exception(const std::string& what);\
				exceptionClassName##Exception();\
			};
		#define LLGL_EXCEPTION(exceptionClassName) class _declspec(dllexport) exceptionClassName##Exception
	#else
		#define LLGL_CLASS(className) class _declspec(dllimport) className; \
			typedef std::shared_ptr<className> className##Ptr; \
			typedef std::weak_ptr<className> className##WeakPtr; \
			class _declspec(dllimport) className 
		#define LLGL_EXCEPTION_DECLARE(exceptionClassName) \
			class _declspec(dllimport) exceptionClassName##Exception : public Llgl::Exception\
			{\
			public:\
				exceptionClassName##Exception(const std::string& what);\
				exceptionClassName##Exception();\
			};
		#define LLGL_EXCEPTION(exceptionClassName) class _declspec(dllimport) exceptionClassName##Exception
	#endif
#else
	#define LLGL_CLASS(className) class className; \
		typedef std::shared_ptr<className> className##Ptr; \
		typedef std::weak_ptr<className> className##WeakPtr; \
		class className 
	#define LLGL_EXCEPTION_DECLARE(exceptionClassName) \
		class exceptionClassName##Exception : public Llgl::Exception\
		{\
		public:\
			exceptionClassName##Exception(const std::string& what);\
			exceptionClassName##Exception();\
		};
	#define LLGL_EXCEPTION(exceptionClassName) class exceptionClassName##Exception
#endif

#ifndef max
	#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif

LLGL_NAMESPACE(Llgl);

LLGL_EXCEPTION(InvalidArgument);
LLGL_EXCEPTION(InvalidOperation);
LLGL_EXCEPTION(OutOfMemory);
LLGL_EXCEPTION(UnexpectedError);
LLGL_EXCEPTION(NotDriveremented);
LLGL_EXCEPTION(UnsupportedFeature);

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
LLGL_CLASS(TextureView);
LLGL_CLASS(Texture1DView);
LLGL_CLASS(Texture1DDataAccessView);
LLGL_CLASS(Texture2DView);
LLGL_CLASS(Texture3DView);
LLGL_CLASS(Texture);
LLGL_CLASS(Texture1DSlice);
LLGL_CLASS(Texture1D);
LLGL_CLASS(Texture2DStream);
LLGL_CLASS(Texture2DSlice);
LLGL_CLASS(Texture2D);
LLGL_CLASS(Texture3DSlice);
LLGL_CLASS(Texture3DStream);
LLGL_CLASS(Texture3D);


LLGL_NAMESPACE_END;