#include "BoxTest.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "ELog.h"
#include "d3dx11Effect.h"

using namespace DirectX;

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };

	XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
}

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

BoxTest::BoxTest(EApp *eApp) :
	_eApp(eApp),
	_eRenderer(eApp->GetRenderer()),
	_eLogger(ELog(L"BoxTest")),
	_vertexBuffer(0),
	_indexBuffer(0),
	_effect(0),
	_effectTechnique(0),
	_effectWorldViewProj(0),
	_inputLayout(0),
	_theta(1.5f*3.1415926535f),
	_phi(0.25f*3.1415926535f),
	_radius(5.0f)
{
	_lastMousePos.x = 0;
	_lastMousePos.y = 0;

	XMMATRIX identity = XMMatrixIdentity();
	XMStoreFloat4x4(&_worldMatrix, identity);
	XMStoreFloat4x4(&_viewMatrix, identity);
	XMStoreFloat4x4(&_projectionMatrix, identity);
}

BoxTest::~BoxTest()
{
	if (_vertexBuffer)
	{
		_vertexBuffer->Release();
		_vertexBuffer = 0;
	}
	if (_indexBuffer)
	{
		_indexBuffer->Release();
		_indexBuffer = 0;
	}
	if (_effect)
	{
		_effect->Release();
		_effect = 0;
	}
	if (_inputLayout)
	{
		_inputLayout->Release();
		_inputLayout = 0;
	}
}

void BoxTest::Init()
{
	BoxTest::OnResize();

	BuildGeometryBuffers();
	BuildFX();
	BuildVertexLayout();

	
}

void BoxTest::BuildGeometryBuffers()
{
	Vertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), (XMFLOAT4)Colors::White },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), (XMFLOAT4)Colors::Black },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), (XMFLOAT4)Colors::Red },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), (XMFLOAT4)Colors::Green },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), (XMFLOAT4)Colors::Blue },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), (XMFLOAT4)Colors::Yellow },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), (XMFLOAT4)Colors::Cyan },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), (XMFLOAT4)Colors::Magenta }
	};

	D3D11_BUFFER_DESC vertexBufferDescription;
	vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDescription.ByteWidth = sizeof(Vertex) * 8;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;
	vertexBufferDescription.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vertexInitialData;
	vertexInitialData.pSysMem = vertices;
	HRESULT hresult = (_eRenderer->GetD3dDevice()->CreateBuffer(&vertexBufferDescription, &vertexInitialData, &_vertexBuffer));
	if (FAILED(hresult))
	{
		_eLogger.LogHResult(hresult);
	}

	UINT indices[] = {
		
		0, 1, 2,	// front
		0, 2, 3,
		4, 6, 5,	// back
		4, 7, 6,
		4, 5, 1,	// left
		4, 1, 0,
		3, 2, 6,	// right
		3, 6, 7,
		1, 5, 6,	// top
		1, 6, 2,
		4, 0, 3,	// bottom
		4, 3, 7
	};

	D3D11_BUFFER_DESC indicesBufferDescription;
	indicesBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	indicesBufferDescription.ByteWidth = sizeof(UINT) * 36;
	indicesBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indicesBufferDescription.CPUAccessFlags = 0;
	indicesBufferDescription.MiscFlags = 0;
	indicesBufferDescription.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA indicesInitializationData;
	indicesInitializationData.pSysMem = indices;
	hresult = (_eRenderer->GetD3dDevice()->CreateBuffer(&indicesBufferDescription, &indicesInitializationData, &_indexBuffer));
	if (FAILED(hresult))
	{
		_eLogger.LogHResult(hresult);
	}
}

void BoxTest::BuildFX()
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMessages = 0;
	HRESULT hresult = D3DCompileFromFile(L"../EEngine/HLSL/color.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, &compiledShader, &compilationMessages);
	
	if (compilationMessages != 0)
	{
		_eLogger.LogLine((char *)compilationMessages->GetBufferPointer());

		compilationMessages->Release();
		compilationMessages = 0;
	}

	if (FAILED(hresult))
	{
		_eLogger.LogHResult(hresult);
	}
	
	hresult = (D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, _eRenderer->GetD3dDevice(), &_effect));
	if (FAILED(hresult))
	{
		_eLogger.LogHResult(hresult);
	}

	if (compiledShader)
	{
		compiledShader->Release();
		compiledShader = 0;
	}

	_effectTechnique = _effect->GetTechniqueByName("ColorTech");
	_effectWorldViewProj = _effect->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void BoxTest::BuildVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC vertexDescription[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3DX11_PASS_DESC effectPassDescription;
	_effectTechnique->GetPassByIndex(0)->GetDesc(&effectPassDescription);
	HRESULT hresult = (_eRenderer->GetD3dDevice()->CreateInputLayout(vertexDescription, 2, effectPassDescription.pIAInputSignature, effectPassDescription.IAInputSignatureSize, &_inputLayout));
	if (FAILED(hresult))
	{
		_eLogger.LogHResult(hresult);
	}
}

void BoxTest::UpdateScene(float deltaTime)
{
	_theta += 1.0f * deltaTime;

	float x = _radius*sinf(_phi)*cosf(_theta);
	float z = _radius*sinf(_phi)*sinf(_theta);
	float y = _radius*cosf(_phi);

	XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR lookAt = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX viewMatrix = XMMatrixLookAtLH(position, lookAt, up);
	XMStoreFloat4x4(&_viewMatrix, viewMatrix);
}

void BoxTest::DrawScene()
{
	_eRenderer->GetD3dImmediateContext()->ClearRenderTargetView(_eRenderer->GetD3dRenderTargetView(), reinterpret_cast<const float*>(&Colors::Magenta));
	_eRenderer->GetD3dImmediateContext()->ClearDepthStencilView(_eRenderer->GetD3dDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	_eRenderer->GetD3dImmediateContext()->IASetInputLayout(_inputLayout);
	_eRenderer->GetD3dImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	_eRenderer->GetD3dImmediateContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	_eRenderer->GetD3dImmediateContext()->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	XMMATRIX world = XMLoadFloat4x4(&_worldMatrix);
	XMMATRIX view = XMLoadFloat4x4(&_viewMatrix);
	XMMATRIX proj = XMLoadFloat4x4(&_projectionMatrix);
	XMMATRIX worldViewProj = world*view*proj;

	_effectWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	D3DX11_TECHNIQUE_DESC techniqueDescription;
	_effectTechnique->GetDesc(&techniqueDescription);
	for (UINT p = 0; p < techniqueDescription.Passes; ++p)
	{
		_effectTechnique->GetPassByIndex(p)->Apply(0, _eRenderer->GetD3dImmediateContext());

		_eRenderer->GetD3dImmediateContext()->DrawIndexed(36, 0, 0);
	}

	HRESULT hresult = (_eRenderer->GetSwapChain()->Present(0, 0));
	if (FAILED(hresult))
	{
		_eLogger.LogHResult(hresult);
	}
}

void BoxTest::OnResize()
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*3.1415926535f, _eRenderer->GetAspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&_projectionMatrix, P);
}

void BoxTest::OnActivate()
{

}

void BoxTest::OnDeactivate()
{

}

void BoxTest::OnMouseDown(WPARAM btnState, int x, int y)
{
	_lastMousePos.x = x;
	_lastMousePos.y = y;

	//SetCapture(window);
}

void BoxTest::OnMouseUp(WPARAM btnState, int x, int y)
{
	//ReleaseCapture();
}


static float Clamp(const float& x, const float& low, const float& high)
{
	return x < low ? low : (x > high ? high : x);
}

void BoxTest::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - _lastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - _lastMousePos.y));

		_theta -= dx;
		_phi -= dy;

		_phi = Clamp(_phi, 0.1f, 3.1415926535f - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		float dx = 0.005f*static_cast<float>(x - _lastMousePos.x);
		float dy = 0.005f*static_cast<float>(y - _lastMousePos.y);

		_radius += dx - dy;

		_radius = Clamp(_radius, 3.0f, 15.0f);
	}

	_lastMousePos.x = x;
	_lastMousePos.y = y;
}