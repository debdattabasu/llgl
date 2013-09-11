#include "Llgl/Library.h"

using namespace Llgl;
Driver::Load loader("Direct3D11");

int main()
{
	auto ctx = Driver::get()->createContext();
	auto buf0 = ctx->createBuffer(32, ctx->createFormat(FormatType::Float, 4));

}