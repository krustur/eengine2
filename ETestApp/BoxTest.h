#pragma once

#include "App.h"
#include "MeshGenerator.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "IEffect.h"
#include "IWindowEventListener.h"
#include <DirectXMath.h>

class BoxTest : public EEngine::IEffect, public EEngine::IWindowEventListener
{
public:
	BoxTest(EEngine::App *app);
	~BoxTest();

	void Init();

	void UpdateScene(float deltaTime);
	void DrawScene();

	void OnResize();
	void OnActivate();
	void OnDeactivate();
	void OnMouseDown(WPARAM buttonState, int x, int y);
	void OnMouseUp(WPARAM buttonState, int x, int y);
	void OnMouseMove(WPARAM buttonState, int x, int y);
	void OnResize(int width, int height);

private:
	EEngine::App* _app;
	EEngine::Renderer* _renderer;
	EEngine::Logger _logger;

	EEngine::MeshGenerator _meshGenerator;
	EEngine::MeshRenderer _meshRenderer;

	EEngine::GameObject _camera;
	EEngine::GameObject _cube1;
	EEngine::GameObject _cube2;
	EEngine::GameObject _cube3;

	DirectX::XMFLOAT4X4 _worldMatrix;

	DirectX::XMFLOAT4X4 _cube1ViewMatrix;
	DirectX::XMFLOAT4X4 _cube2ViewMatrix;
	DirectX::XMFLOAT4X4 _cube3ViewMatrix;

	DirectX::XMFLOAT4X4 _projectionMatrix;

	float _theta;
	float _phi;
	float _radius;

	POINT _lastMousePos;

	EEngine::Mesh *_cube1Mesh;
	EEngine::Mesh *_cube2Mesh;
	EEngine::Mesh *_cube3Mesh;
};

