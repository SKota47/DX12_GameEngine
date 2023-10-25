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
	//ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	//ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g
	ID3D12PipelineState* pipelineState = nullptr; // �p�C�v�����X�e�[�g
	ID3D12RootSignature* rootSignature;	// ���[�g�V�O�l�`��
	D3D12_VERTEX_BUFFER_VIEW vbView{};	// ���_�o�b�t�@�r���[�̍쐬
	//XMFLOAT3* vertex;
	XMFLOAT3 vertices[3] =
	{ { -0.5f,-0.5f,0.f },
	{ -0.5f,+0.5f,0.f },
	{ +0.5f,-0.5f,0.f } };
	//UINT sizeVB;

	ID3D12Resource* vertBuff = nullptr;
};