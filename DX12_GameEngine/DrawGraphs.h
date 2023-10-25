#pragma once
#include "WinApp.h"
#include "Math.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
class DrawGraphs
{
public:
	DrawGraphs(WinApp* wp);
	void Init(XMFLOAT3& ver);
	void Update();
	void PreUpdate();
	void PostUpdate();
	void ShaderErrorCheck();
private:
	WinApp* wp = nullptr;
	HRESULT result = S_OK;
	//ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
	//ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
	ID3DBlob* errorBlob = nullptr; // エラーオブジェクト
	ID3D12PipelineState* pipelineState = nullptr; // パイプランステート
	ID3D12RootSignature* rootSignature;	// ルートシグネチャ
	D3D12_VERTEX_BUFFER_VIEW vbView{};	// 頂点バッファビューの作成
	//XMFLOAT3* vertex;
	XMFLOAT3 vertices[3] =
	{ { -0.5f,-0.5f,0.f },
	{ -0.5f,+0.5f,0.f },
	{ +0.5f,-0.5f,0.f } };
	//UINT sizeVB;

	ID3D12Resource* vertBuff = nullptr;
};