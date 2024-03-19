#pragma once
#include "Bindable.h"

namespace Bind
{
class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
	IndexBuffer(Graphics& gfx, std::string tag, const std::vector<unsigned short>& indices);
	void Bind(Graphics& gfx) noexcept override;
	UINT GetCount() const noexcept;
	DECLARE_RESOLVE(IndexBuffer, Graphics& gfx, const std::string& tag, const std::vector<unsigned short>& indices);
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
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};
}




