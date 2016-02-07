#pragma once

#include <d3d11.h>
#include "Logger.h"
#include "IWindowEventListener.h"
#include "Color.h"

namespace EEngine
{
	typedef enum RENDERER_CLEAR_FLAG
	{
		RENDERER_CLEAR_DEPTH = 0x1L,
		RENDERER_CLEAR_STENCIL = 0x2L
	} 	RENDERER_CLEAR_FLAG;

	class Renderer final : public IWindowEventListener
	{
	public:
		Renderer(HWND windowHandle);
		~Renderer();

		virtual bool Init();

		void OnActivate();
		void OnDeactivate();
		void OnMouseDown(WPARAM buttonState, int x, int y);
		void OnMouseUp(WPARAM buttonState, int x, int y);
		void OnMouseMove(WPARAM buttonState, int x, int y);
		void OnResize(int width, int height);

		void ClearRenderTargetView(Color color);
		void ClearDepthStencilView(unsigned int clearFlags, float depth, int stencil);

		void Present();

		ID3D11Device *GetD3dDevice();
		ID3D11DeviceContext* GetD3dImmediateContext();
		ID3D11RenderTargetView* GetD3dRenderTargetView();
		ID3D11DepthStencilView* GetD3dDepthStencilView();
		IDXGISwapChain* GetSwapChain();
		float GetAspectRatio() const;

	private:
		HWND _windowHandle;

		void OnResize();

		int _clientWidth;
		int _clientHeight;
		bool _enable4xMsaa;
		UINT _4xMsaaQuality;

		Logger _logger;

		ID3D11Device* _d3dDevice;
		ID3D11DeviceContext* _d3dImmediateContext;
		IDXGISwapChain* _swapChain;
		ID3D11Texture2D* _depthStencilBuffer;
		ID3D11RenderTargetView* _renderTargetView;
		ID3D11DepthStencilView* _depthStencilView;
		D3D11_VIEWPORT _screenViewport;
		D3D_DRIVER_TYPE _d3dDriverType;
	};
}