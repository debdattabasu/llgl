#include "Llgl/Library.h"
#include <iostream>
using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf = ctx->createBuffer(32, ctx->createFormat(FormatType::Float, 4));
	auto bufStream = ctx->createBuffer(32, ctx->createFormat(FormatType::Float, 4), true);
	void* mem = ctx->mapResource(bufStream, 0, 0, MapType::Write);
	memset(mem, 1, 32*4*4);
	ctx->unmapResource(bufStream, 0,0);
	ctx->copyResource(bufStream, 0, 0, 0, 32, 1, 1, 0, 0, buf, 0, 0, 0, 0, 0);
	void* mem1 = ctx->mapResource(bufStream, 0, 0, MapType::Read);
	if(memcmp(mem1, mem, 32*4*4) == 0)
	{
		std::cout<<"passed";
	}
	else
	{
		std::cout<<"failed";
	}
}