#include "Llgl/Library.h"
#include <iostream>
using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf = ctx->createTexture2D(32, 32, 1, 1, ctx->createFormat(FormatType::Float, 1));
	auto bufStream = ctx->createTexture2DStream(32, 32, ctx->createFormat(FormatType::Float, 1));
	auto bufStream1 = ctx->createTexture2DStream(32, 32, ctx->createFormat(FormatType::Float, 1));
	{
		void* mem = bufStream->map();
		memset(mem, 1, 32*32*4);
		bufStream->unmap();
	}
	buf->write(bufStream, 0, 0, 0, 0);
	buf->read(bufStream1, 0, 0, 0, 0);
	void* mem = bufStream->map();
	void* mem1 = bufStream1->map();

	if(memcmp(mem1, mem, 32*32*4) == 0)
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