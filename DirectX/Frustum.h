#pragma once
#include "Drawable.h"

class Frustum : public Drawable
{
public:
	Frustum(Graphics& gfx, float width, float height, float nearZ, float farZ);
	void SetVertices(Graphics& gfx, float width, float height, float nearZ, float farZ);
	void SetPos(DirectX::XMFLOAT3 pos) noexcept;
	void SetRotation(DirectX::XMFLOAT3 rot) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	DirectX::XMFLOAT3 pos = { 0.f, 0.f, 0.f };
	DirectX::XMFLOAT3 rot = { 0.f, 0.f, 0.f };
};

