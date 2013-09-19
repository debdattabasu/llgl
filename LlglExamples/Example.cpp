#include "Llgl/Library.h"
#include <iostream>
using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf = ctx->createBuffer(32, ctx->createFormat(FormatType::Float, 1));
	auto bufStream = ctx->createBufferStream(32, ctx->createFormat(FormatType::Float, 1));
	auto bufStream1 = ctx->createBufferStream(32, ctx->createFormat(FormatType::Float, 1));
	{
		auto mem = bufStream->map();
		memset(mem.data, 1, 32*4);
		bufStream->unmap();
	}
	bufStream->writeData(buf, 0);
	bufStream1->readData(buf, 0);
	auto mem = bufStream->map();
	auto mem1 = bufStream1->map();

	bool passed = true;
	if(memcmp(mem1.data, mem.data, 32*4))
	{
		passed = false;
	}
	passed? std::cout<<"passed" : std::cout<<"failed";

	bufStream->unmap();
	bufStream1->unmap();
}