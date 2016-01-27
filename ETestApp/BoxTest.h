#pragma once

#include <d3d11.h>
#include "d3dx11effect.h"
#include "Eapp.h"
#include "ERenderer.h"
#include "IEEffect.h"
#include <DirectXMath.h>



class BoxTest : public IEEffect
{
public:
	BoxTest(EApp *eApp);
	~BoxTest();

	void Init();

	void BuildGeometryBuffers();
	void BuildFX();
	void BuildVertexLayout();

	void UpdateScene(float deltaTime);
	void DrawScene();
	void OnResize();

private:
	EApp* _eApp;
	ERenderer* _eRenderer;

	ID3D11Buffer* _vertexBuffer;
	ID3D11Buffer* _indexBuffer;

	ID3DX11Effect* _effect;
	ID3DX11EffectTechnique* _effectTechnique;
	ID3DX11EffectMatrixVariable* _effectWorldViewProj;

	ID3D11InputLayout* _inputLayout;

	DirectX::XMFLOAT4X4 _worldMatrix;
	DirectX::XMFLOAT4X4 _viewMatrix;
	DirectX::XMFLOAT4X4 _projectionMatrix;

	float _theta;
	float _phi;
	float _radius;

	POINT _lastMousePos;
};

