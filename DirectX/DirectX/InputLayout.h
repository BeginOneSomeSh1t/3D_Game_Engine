#pragma once
#include "Bindable.h"
#include "Vertex.h"

namespace Bind
{
	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx,
			VertexSystem::VertexLayout layout,
			ID3DBlob* pVertexShaderBytecode);
		void Bind(Graphics& gfx) noexcept override;
		DECLARE_RESOLVE(InputLayout, Graphics& gfx, const VertexSystem::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode);
		DECLARE_GENERATEUID(const VertexSystem::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode = nullptr);
		DECLARE_OVERRIDE_GETUID();
	protected:
		VertexSystem::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}

