#include "Llgl/Library.h"
#include <iostream>
using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf = ctx->createTexture3D(32, 1, 1, 1, ctx->createFormat(FormatType::Float, 4));
	auto bufStream = ctx->createTexture3DStream(32, 1, 1, ctx->createFormat(FormatType::Float, 4));
	auto bufStream1 = ctx->createTexture3DStream(32, 1, 1, ctx->createFormat(FormatType::Float, 4));
	{
		void* mem = bufStream->map();
		memset(mem, 1, 32*16);
		bufStream->unmap();
	}
	buf->write(bufStream, 0, 0, 0, 0);
	buf->read(bufStream1, 0, 0, 0, 0);
	void* mem = bufStream->map();
	void* mem1 = bufStream1->map();

	if(memcmp(mem1, mem, 32*16) == 0)
	{
		std::cout<<"passed";
	}
	else
	{
		std::cout<<"failed";
	}
	bufStream->unmap();
	bufStream1->unmap();
}