#include "Llgl/Library.h"
#include <iostream>
using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf = ctx->createBuffer(32, ctx->createFormat(FormatType::Float, 1));
	std::vector<float> data(32);
	for(int i = 0; i < 32; i++)
	{
		data[i] = 2;
	}
	buf->getDataAccessView(0, 32)->setData(&data[0]);
	std::vector<float> dataRet(32);
	buf->getDataAccessView(0, 32)->getData(&dataRet[0]);

	bool passed = true;
	for(int i = 0; i < 32; i++)
	{
		if(data[i] != dataRet[i] || data[i] != 2)
		{
			passed = false;
			break;
		}
		
	}
	passed? std::cout<<"passed" : std::cout<<"failed";
}