#pragma once
#include "MyWin.h" // <Windows.h> with some macros
#include "MyException.h"
#include <d3d11.h>
#include "dxerr.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <random>
#include <wrl.h>
#include <cassert>
#include <vector>
#include <memory>
#include "DxgiInfoManager.h" //for debug
#include "ConditionalNoexcept.h"

namespace Bind
{
	class Bindable;
}



class Graphics
{
	friend Bind::Bindable;
public:
	class GFXException : public MyException
	{
		using MyException::MyException;
	};
	class HrException : public GFXException
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> messages = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public GFXException
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics( HWND hWnd, int width, int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noxnd;
public:
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
public:
	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;
private:
	bool imguiEnabled{ true };
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
	
#ifndef NDEBUG 
	DxgiInfoManager infoManager;
#endif // !NDEBUG

	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr <IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr <ID3D11DepthStencilView> pDSV;
	Microsoft::WRL::ComPtr <ID3D11SamplerState> pSampState;
	
};

