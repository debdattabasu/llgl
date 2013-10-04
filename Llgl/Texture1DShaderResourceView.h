#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DShaderResourceView) : public Texture1DView
{
public:
	friend class Texture1D;
	virtual ~Texture1DShaderResourceView() override;

protected:
	Texture1DShaderResourceView(Texture1DPtr parentTexture);
	virtual void initializeDriver() = 0;
private:
	void initialize();

};

LLGL_NAMESPACE_END;