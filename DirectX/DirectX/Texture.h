#pragma once
#include "Bindable.h"

class Surface;

namespace Bind
{
	class Texture : public Bindable
	{
	public:
		Texture(Graphics& gfx, const std::string& path, UINT slot = 0);
		void Bind(Graphics& gfx) noexcept override;
		DECLARE_RESOLVE(Texture, Graphics& gfx, const std::string& path, UINT slot = 0);
		DECLARE_GENERATEUID(const std::string& path, UINT slot = 0);
		DECLARE_OVERRIDE_GETUID();
	private:
		unsigned int slot;
	protected:
		std::string path;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	};
}

