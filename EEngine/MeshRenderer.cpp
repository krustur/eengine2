#include "MeshRenderer.h"

namespace EEngine
{

	MeshRenderer::MeshRenderer(Renderer &renderer) :
		_renderer(renderer),
		_logger(L"MeshRenderer")
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::RenderMesh(Mesh *mesh, DirectX::XMMATRIX *worldViewProj)
	{
		_renderer.GetD3dImmediateContext()->IASetInputLayout(mesh->GetInputLayout());
		_renderer.GetD3dImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT stride = mesh->GetStride();
		UINT offset = 0;
		auto vertexBuffer = mesh->GetVertexBuffer();
		_renderer.GetD3dImmediateContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		_renderer.GetD3dImmediateContext()->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		mesh->GetEffectWorldViewProj()->SetMatrix(reinterpret_cast<float*>(worldViewProj));

		D3DX11_TECHNIQUE_DESC techniqueDescription;
		mesh->GetEffectTechnique()->GetDesc(&techniqueDescription);
		for (UINT p = 0; p < techniqueDescription.Passes; ++p)
		{
			mesh->GetEffectTechnique()->GetPassByIndex(p)->Apply(0, _renderer.GetD3dImmediateContext());

			_renderer.GetD3dImmediateContext()->DrawIndexed(36, 0, 0);
		}
	}
}