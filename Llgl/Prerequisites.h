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

#define LLGL_ENUM(enumName) enum class enumName : uint32_t
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
			typedef std::shared_ptr<className> className##WeakPtr; \
			class _declspec(dllexport) className 
		#define LLGL_EXCEPTION_DECLARE(exceptionClassName) \
			class _declspec(dllexport) exceptionClassName##Exception : public Llgl::Exception\
			{\
			public:\
				exceptionClassName##Exception(const std::string& what);\
				exceptionClassName##Exception();\
			};
	#else
		#define LLGL_CLASS(className) class _declspec(dllimport) className; \
			typedef std::shared_ptr<className> className##Ptr; \
			typedef std::shared_ptr<className> className##WeakPtr; \
			class _declspec(dllimport) className 
		#define LLGL_EXCEPTION_DECLARE(exceptionClassName) \
			class _declspec(dllimport) exceptionClassName##Exception : public Llgl::Exception\
			{\
			public:\
				exceptionClassName##Exception(const std::string& what);\
				exceptionClassName##Exception();\
			};
	#endif
#else
	#define LLGL_CLASS(className) class className; \
		typedef std::shared_ptr<className> className##Ptr; \
		typedef std::shared_ptr<className> className##WeakPtr; \
		class className 
	#define LLGL_EXCEPTION_DECLARE(exceptionClassName) \
		class exceptionClassName##Exception : public Llgl::Exception\
		{\
		public:\
			exceptionClassName##Exception(const std::string& what);\
			exceptionClassName##Exception();\
		};
#endif


LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Driver);
LLGL_CLASS(Context);
LLGL_CLASS(Object);

LLGL_NAMESPACE_END




