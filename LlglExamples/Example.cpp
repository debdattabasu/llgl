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
		auto mem = bufStream->map();

		for(uint32_t i = 0; i < 32; i++)
		{
			memset(mem.data, i, 32*4);
			mem.data += mem.rowPitch;
		}
		
		bufStream->unmap();
	}
	buf->copyFrom(bufStream, 0, 0, 32, 32, 0, 0, 0, 0);
	bufStream1->copyFrom(buf, 0, 0, 32, 32, 0, 0, 0, 0);
	auto mem = bufStream->map();
	auto mem1 = bufStream1->map();

	bool passed = true;

	for(uint32_t i = 0; i < 32; i++)
	{
		if(memcmp(mem1.data, mem.data, 32*4))
		{
			passed = false;
			break;
		}
		mem1.data += mem1.rowPitch;
		mem.data += mem.rowPitch;
	}

	passed? std::cout<<"passed" : std::cout<<"failed";

	bufStream->unmap();
	bufStream1->unmap();
}