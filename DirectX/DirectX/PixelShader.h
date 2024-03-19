#pragma once
#include "Bindable.h"

namespace Bind
{
	class PixelShader : public Bindable
	{
	public:
		PixelShader(Graphics& gfx, const std::string& path);
		void Bind(Graphics& gfx) noexcept override;
		DECLARE_RESOLVE(PixelShader, Graphics& gfx, const std::string& path);
		DECLARE_GENERATEUID(const std::string& path);
		DECLARE_OVERRIDE_GETUID();
	protected:
		std::string path;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	};


}