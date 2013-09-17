#include "Llgl/Library.h"
#include <iostream>
using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf = ctx->createTexture2D(32, 32, 1, 1, ctx->createFormat(FormatType::Float, 1));
	auto bufStream = ctx->createTexture2D(32, 32, 1, 1, ctx->createFormat(FormatType::Float, 1), true);
	void* mem = bufStream->map(0, 0, MapType::Write);
	memset(mem, 45, 32*32*4);
	bufStream->unmap(0,0);
	buf->copyFrom(bufStream, 0, 0, 32, 32, 0, 0, 0, 0, 0, 0);
	void* mem1 = bufStream->map(0, 0, MapType::Read);

	if(memcmp(mem1, mem, 32*32*4) == 0)
	{
		std::cout<<"passed";
	}
	else
	{
		std::cout<<"failed";
	}

	bufStream->unmap(0, 0);
}