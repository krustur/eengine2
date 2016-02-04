#include "BoxTest.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <iostream>

#include "ELog.h"
#include "EColor.h"
#include "EMath.h"

#include "d3dx11Effect.h"

BoxTest::BoxTest(EEngine::EApp *eApp) :
	_eApp(eApp),
	_eRenderer(eApp->GetRenderer()),
	_eLogger(L"BoxTest"),
	_meshGenerator(*eApp->GetRenderer()),
	_meshRenderer(*eApp->GetRenderer()),
	_theta(1.5f*EEngine::EMath::Pi),
	_phi(0.25f*EEngine::EMath::Pi),
	_radius(5.0f),
	_cube(nullptr)
{
	_lastMousePos.x = 0;
	_lastMousePos.y = 0;

	DirectX::XMMATRIX identity = DirectX::XMMatrixIdentity();
	XMStoreFloat4x4(&_worldMatrix, identity);
	XMStoreFloat4x4(&_viewMatrix, identity);
	XMStoreFloat4x4(&_projectionMatrix, identity);
}

BoxTest::~BoxTest()
{
}

void BoxTest::Init()
{
	_cube = _meshGenerator.GenerateMesh();

	BoxTest::OnResize();
}

void BoxTest::UpdateScene(float deltaTime)
{
	_theta += 1.0f * deltaTime;

	float x = _radius*sinf(_phi)*cosf(_theta);
	float z = _radius*sinf(_phi)*sinf(_theta);
	float y = _radius*cosf(_phi);

	DirectX::XMVECTOR position = DirectX::XMVectorSet(x, y, z, 1.0f);
	DirectX::XMVECTOR lookAt = DirectX::XMVectorZero();
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(position, lookAt, up);
	XMStoreFloat4x4(&_viewMatrix, viewMatrix);
}

void BoxTest::DrawScene()
{
	DirectX::XMMATRIX world = XMLoadFloat4x4(&_worldMatrix);
	DirectX::XMMATRIX view = XMLoadFloat4x4(&_viewMatrix);
	DirectX::XMMATRIX proj = XMLoadFloat4x4(&_projectionMatrix);
	DirectX::XMMATRIX worldViewProj = world*view*proj;

	_meshRenderer.RenderMesh(_cube, &worldViewProj);	
}

void BoxTest::OnResize()
{
	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(0.25f*EEngine::EMath::Pi, _eRenderer->GetAspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&_projectionMatrix, P);
}

void BoxTest::OnActivate() {}

void BoxTest::OnDeactivate() {}

void BoxTest::OnMouseDown(WPARAM btnState, int x, int y)
{
	_lastMousePos.x = x;
	_lastMousePos.y = y;
}

void BoxTest::OnMouseUp(WPARAM btnState, int x, int y) {}

void BoxTest::OnResize(int width, int height) {}

static float Clamp(const float& x, const float& low, const float& high)
{
	return x < low ? low : (x > high ? high : x);
}

void BoxTest::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		float dx = DirectX::XMConvertToRadians(0.25f*static_cast<float>(x - _lastMousePos.x));
		float dy = DirectX::XMConvertToRadians(0.25f*static_cast<float>(y - _lastMousePos.y));

		_theta -= dx;
		_phi -= dy;

		_phi = Clamp(_phi, 0.1f, EEngine::EMath::Pi - 0.1f);
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