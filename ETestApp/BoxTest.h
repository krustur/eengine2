#pragma once

#include "Eapp.h"
#include "EMeshGenerator.h"
#include "EMeshRenderer.h"
#include "GameObject.h"
#include "IEEffect.h"
#include "IEWindowEventListener.h"
#include <DirectXMath.h>

class BoxTest : public EEngine::IEEffect, public EEngine::IEWindowEventListener
{
public:
	BoxTest(EEngine::EApp *eApp);
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
	EEngine::EApp* _eApp;
	EEngine::ERenderer* _eRenderer;
	EEngine::ELog _eLogger;

	EEngine::EMeshGenerator _meshGenerator;
	EEngine::EMeshRenderer _meshRenderer;

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

	EEngine::EMesh *_cube1Mesh;
	EEngine::EMesh *_cube2Mesh;
	EEngine::EMesh *_cube3Mesh;
};

