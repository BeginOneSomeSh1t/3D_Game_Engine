#pragma once
#include "Bindable.h"

namespace Bind
{
	class VertexShader : public Bindable
	{
	public:
		VertexShader(Graphics& gfx, const std::string& path);
		void Bind(Graphics& gfx) noexcept override;
		ID3DBlob* GetBytecode() const noexcept;
		DECLARE_RESOLVE(VertexShader, Graphics& gfx, const std::string& path);
		DECLARE_GENERATEUID(const std::string& path);
		DECLARE_OVERRIDE_GETUID();
	protected:
		std::string path;
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;

	};
}

