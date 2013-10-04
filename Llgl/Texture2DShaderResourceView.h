#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DShaderResourceView) : public Texture2DView
{
public:
	friend class Texture2D;
	virtual ~Texture2DShaderResourceView() override;

protected:
	Texture2DShaderResourceView(Texture2DPtr parentTexture);
	virtual void initializeDriver() = 0;
private:
	void initialize();

};

LLGL_NAMESPACE_END;