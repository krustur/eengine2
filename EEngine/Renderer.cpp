#include "Renderer.h"

#include <d3d11.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#include "Logger.h"

namespace EEngine
{
	Renderer::Renderer(HWND windowHandle) :
		_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
		_clientWidth(800),
		_clientHeight(600),
		_enable4xMsaa(false),
		_windowHandle(windowHandle),
		_4xMsaaQuality(0),
		_d3dDevice(0),
		_d3dImmediateContext(0),
		_swapChain(0),
		_depthStencilBuffer(0),
		_renderTargetView(0),
		_depthStencilView(0),
		_logger(L"Renderer")
	{
	}

	Renderer::~Renderer()
	{
		if (_renderTargetView)
		{
			_renderTargetView->Release();
			_renderTargetView = 0;
		}
		if (_depthStencilView)
		{
			_depthStencilView->Release();
			_depthStencilView = 0;
		}
		if (_swapChain)
		{
			_swapChain->Release();
			_swapChain = 0;
		}
		if (_depthStencilBuffer)
		{
			_depthStencilBuffer->Release();
			_depthStencilBuffer = 0;
		}

		if (_d3dImmediateContext)
		{
			_d3dImmediateContext->ClearState();
			_d3dImmediateContext->Release();
			_d3dImmediateContext = 0;
		}
		if (_d3dDevice)
		{
			_d3dDevice->Release();
			_d3dDevice = 0;
		}
	}

	bool Renderer::Init()
	{
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hresult = D3D11CreateDevice(0, _d3dDriverType, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &_d3dDevice, &featureLevel, &_d3dImmediateContext);

		if (FAILED(hresult))
		{
			// TODO: Throw exceptions
			_logger.LogLine(L"Failed to initialize Renderer: Failed to create D3D11CreateDevice.");
			_logger.LogHResult(hresult);
			MessageBox(0, L"Failed to initialize Renderer, see log for details.", 0, 0);
			return false;
		}

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
			//if (featureLevel != 0xc000)
		{
			// TODO: Throw exceptions
			_logger.LogLine(L"Failed to initialize Renderer: Required D3D feature level 11 not supported.");
			MessageBox(0, L"Failed to initialize Renderer, see log for details.", 0, 0);
			return false;
		}

		hresult = (_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}
		assert(_4xMsaaQuality > 0);

		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		swapChainDescription.BufferDesc.Width = _clientWidth;
		swapChainDescription.BufferDesc.Height = _clientHeight;
		swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (_enable4xMsaa)
		{
			swapChainDescription.SampleDesc.Count = 4;
			swapChainDescription.SampleDesc.Quality = _4xMsaaQuality - 1;
		}
		else
		{
			swapChainDescription.SampleDesc.Count = 1;
			swapChainDescription.SampleDesc.Quality = 0;
		}
		swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDescription.BufferCount = 1;
		swapChainDescription.OutputWindow = _windowHandle;
		swapChainDescription.Windowed = true;
		swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDescription.Flags = 0;

		IDXGIDevice* dxgiDevice = 0;
		hresult = (_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		IDXGIAdapter* dxgiAdapter = 0;
		hresult = (dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		IDXGIFactory* dxgiFactory = 0;
		hresult = (dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		hresult = (dxgiFactory->CreateSwapChain(_d3dDevice, &swapChainDescription, &_swapChain));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		if (dxgiDevice)
		{
			dxgiDevice->Release();
			dxgiDevice = 0;
		}
		if (dxgiAdapter)
		{
			dxgiAdapter->Release();
			dxgiAdapter = 0;
		}
		if (dxgiFactory)
		{
			dxgiFactory->Release();
			dxgiFactory = 0;
		}

		OnResize();

		return true;
	}

	void Renderer::OnResize()
	{
		_logger.FormatLine(_logger << "OnResize(), " << _clientWidth << ", " << _clientHeight);

		assert(_d3dImmediateContext);
		assert(_d3dDevice);
		assert(_swapChain);

		if (_renderTargetView)
		{
			_renderTargetView->Release();
			_renderTargetView = 0;
		}
		if (_depthStencilView)
		{
			_depthStencilView->Release();
			_depthStencilView = 0;
		}
		if (_depthStencilBuffer)
		{
			_depthStencilBuffer->Release();
			_depthStencilBuffer = 0;
		}

		// Resize the swap chain and recreate the render target view.

		HRESULT hresult = (_swapChain->ResizeBuffers(1, _clientWidth, _clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		ID3D11Texture2D* backBuffer;
		hresult = (_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		hresult = (_d3dDevice->CreateRenderTargetView(backBuffer, 0, &_renderTargetView));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		if (backBuffer)
		{
			backBuffer->Release();
			backBuffer = 0;
		}

		D3D11_TEXTURE2D_DESC depthStencilDescription;
		depthStencilDescription.Width = _clientWidth;
		depthStencilDescription.Height = _clientHeight;
		depthStencilDescription.MipLevels = 1;
		depthStencilDescription.ArraySize = 1;
		depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (_enable4xMsaa)
		{
			depthStencilDescription.SampleDesc.Count = 4;
			depthStencilDescription.SampleDesc.Quality = _4xMsaaQuality - 1;
		}
		else
		{
			depthStencilDescription.SampleDesc.Count = 1;
			depthStencilDescription.SampleDesc.Quality = 0;
		}
		depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDescription.CPUAccessFlags = 0;
		depthStencilDescription.MiscFlags = 0;
		hresult = (_d3dDevice->CreateTexture2D(&depthStencilDescription, 0, &_depthStencilBuffer));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		hresult = (_d3dDevice->CreateDepthStencilView(_depthStencilBuffer, 0, &_depthStencilView));
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}

		_d3dImmediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

		_screenViewport.TopLeftX = 0;
		_screenViewport.TopLeftY = 0;
		_screenViewport.Width = static_cast<float>(_clientWidth);
		_screenViewport.Height = static_cast<float>(_clientHeight);
		_screenViewport.MinDepth = 0.0f;
		_screenViewport.MaxDepth = 1.0f;

		_d3dImmediateContext->RSSetViewports(1, &_screenViewport);
	}

	void Renderer::ClearRenderTargetView(Color color)
	{
		_d3dImmediateContext->ClearRenderTargetView(_renderTargetView, reinterpret_cast<const float*>(&color));


	}

	void Renderer::ClearDepthStencilView(unsigned int clearFlags, float depth, int stencil)
	{
		_d3dImmediateContext->ClearDepthStencilView(_depthStencilView, clearFlags, depth, stencil);

	}

	void Renderer::Present()
	{
		HRESULT hresult = _swapChain->Present(0, 0);		
		if (FAILED(hresult))
		{
			_logger.LogHResult(hresult);
		}
	}

	void Renderer::OnActivate() {}

	void Renderer::OnDeactivate() {}

	void Renderer::OnMouseDown(WPARAM buttonState, int x, int y) {}

	void Renderer::OnMouseUp(WPARAM buttonState, int x, int y) {}

	void Renderer::OnMouseMove(WPARAM buttonState, int x, int y) {}

	void Renderer::OnResize(int width, int height)
	{
		_clientWidth = width;
		_clientHeight = height;
		OnResize();
	}

	ID3D11Device * Renderer::GetD3dDevice()
	{
		return _d3dDevice;
	}

	ID3D11DeviceContext * Renderer::GetD3dImmediateContext()
	{
		return _d3dImmediateContext;
	}

	ID3D11RenderTargetView * Renderer::GetD3dRenderTargetView()
	{
		return _renderTargetView;
	}

	ID3D11DepthStencilView * Renderer::GetD3dDepthStencilView()
	{
		return _depthStencilView;
	}

	IDXGISwapChain * Renderer::GetSwapChain()
	{
		return _swapChain;
	}

	float Renderer::GetAspectRatio() const
	{
		return static_cast<float>(_clientWidth) / _clientHeight;
	}
}