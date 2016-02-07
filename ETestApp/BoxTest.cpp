#include "BoxTest.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <iostream>

#include "Logger.h"
#include "Color.h"
#include "EEngineMath.h"

#include "d3dx11Effect.h"

BoxTest::BoxTest(EEngine::App *app) :
	_app(app),
	_renderer(app->GetRenderer()),
	_logger(L"BoxTest"),
	_meshGenerator(*app->GetRenderer()),
	_meshRenderer(*app->GetRenderer()),
	_theta(1.5f*EEngine::EEngineMath::Pi),
	_phi(0.25f*EEngine::EEngineMath::Pi),
	_radius(5.0f),
	_cube1Mesh(nullptr),
	_cube2Mesh(nullptr),
	_cube3Mesh(nullptr),
	_camera(0, 2, -5, 0, 0, 0),
	_cube1(0, 0, 0, 0, 0, 0),
	_cube2(-1.5, 0, 0, 0, 0, 30),
	_cube3(3, 0, 1.5, 0, 45, 0)
{
	_lastMousePos.x = 0;
	_lastMousePos.y = 0;

	DirectX::XMMATRIX identity = DirectX::XMMatrixIdentity();
	XMStoreFloat4x4(&_worldMatrix, identity);

	XMStoreFloat4x4(&_projectionMatrix, identity);
}

BoxTest::~BoxTest()
{
}

void BoxTest::Init()
{
	_cube1Mesh = _meshGenerator.GenerateMesh();
	_cube2Mesh = _meshGenerator.GenerateMesh();
	_cube3Mesh = _meshGenerator.GenerateMesh();

	BoxTest::OnResize();
}

void BoxTest::UpdateScene(float deltaTime)
{
	_theta += 1.0f * deltaTime;

	auto cube1Rotation = _cube1.GetRotation();
	cube1Rotation.y += 1.0f * deltaTime;
	_cube1.SetRotation(cube1Rotation);

	DirectX::XMMATRIX cube1Transform = _cube1.GetLocalTransform();
	DirectX::XMMATRIX cube2Transform = _cube2.GetLocalTransform();
	DirectX::XMMATRIX cube3Transform = _cube3.GetLocalTransform();


	DirectX::XMMATRIX inverseCameraTransform = _camera.GetInversedLocalTransform();

	DirectX::XMMATRIX cube1ViewTransform = cube1Transform * inverseCameraTransform;
	XMStoreFloat4x4(&_cube1ViewMatrix, cube1ViewTransform);

	DirectX::XMMATRIX cube2ViewTransform = cube2Transform * inverseCameraTransform;
	XMStoreFloat4x4(&_cube2ViewMatrix, cube2ViewTransform);

	DirectX::XMMATRIX cube3ViewTransform = cube3Transform * inverseCameraTransform;
	XMStoreFloat4x4(&_cube3ViewMatrix, cube3ViewTransform);
}

void BoxTest::DrawScene()
{
	_renderer->ClearRenderTargetView(EEngine::Colors::LightSteelBlue);
	_renderer->ClearDepthStencilView(EEngine::RENDERER_CLEAR_DEPTH | EEngine::RENDERER_CLEAR_STENCIL, 1.0f, 0);

	DirectX::XMMATRIX world = XMLoadFloat4x4(&_worldMatrix);
	DirectX::XMMATRIX proj = XMLoadFloat4x4(&_projectionMatrix);

	DirectX::XMMATRIX view = XMLoadFloat4x4(&_cube1ViewMatrix);
	DirectX::XMMATRIX worldViewProj = world*view*proj;

	_meshRenderer.RenderMesh(_cube1Mesh, &worldViewProj);

	view = XMLoadFloat4x4(&_cube2ViewMatrix);
	worldViewProj = world*view*proj;

	_meshRenderer.RenderMesh(_cube2Mesh, &worldViewProj);

	view = XMLoadFloat4x4(&_cube3ViewMatrix);
	worldViewProj = world*view*proj;

	_meshRenderer.RenderMesh(_cube3Mesh, &worldViewProj);

	_renderer->Present();
}

void BoxTest::OnResize()
{
	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(1.0472, _renderer->GetAspectRatio(), 0.3f, 1000.0f);
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

		_phi = Clamp(_phi, 0.1f, EEngine::EEngineMath::Pi - 0.1f);
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