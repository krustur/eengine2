#pragma once

#include <d3d11.h>
#include "ELog.h"

class ERenderer final
{
public:
	ERenderer(HWND windowHandle);
	~ERenderer();

	virtual bool Init(); 	
	void OnResize();

	ID3D11Device *GetD3dDevice();
	ID3D11DeviceContext* GetD3dImmediateContext();
	ID3D11RenderTargetView* GetD3dRenderTargetView();
	ID3D11DepthStencilView* GetD3dDepthStencilView();
	IDXGISwapChain* GetSwapChain();
	float ERenderer::GetAspectRatio() const;

private:
	HWND _windowHandle;

	int _clientWidth;
	int _clientHeight;
	bool _enable4xMsaa;
	UINT _4xMsaaQuality;

	//bool _appPaused;
	//bool _minimized;
	//bool _maximized;
	//bool _resizing;

	ELog *_eLog;

	ID3D11Device* _d3dDevice;
	ID3D11DeviceContext* _d3dImmediateContext;
	IDXGISwapChain* _swapChain;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11DepthStencilView* _depthStencilView;
	D3D11_VIEWPORT _screenViewport;
	D3D_DRIVER_TYPE _d3dDriverType;
};