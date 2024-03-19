#pragma once
#include "Bindable.h"
#include "GraphicsThrowMacros.h"
#include "Vertex.h"

namespace Bind
{
	class VertexBuffer : public Bindable
	{
	public:
		VertexBuffer(Graphics& gfx,const std::string& tag ,const VERSYS_ VertexBuffer& vbuf);
		VertexBuffer(Graphics& gfx, const VERSYS_ VertexBuffer& vbuf);
		void Bind(Graphics& gfx) noexcept override;
		DECLARE_RESOLVE(VertexBuffer, Graphics& gfx, const std::string& tag, const VERSYS_ VertexBuffer& vbuf);
		template<typename...Ignore>
		DECLARE_GENERATEUID(const std::string& tag, Ignore&&... ignore)
		{
			return GenerateUID_(tag);
		}
		DECLARE_OVERRIDE_GETUID();
	private:
		static std::string GenerateUID_(const std::string& tag);
	protected:
		std::string tag;
		UINT stride;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	};
}

