#include "WinApp.h"
#include "Math.h"
#include <Windows.h>
#include "DrawGraphs.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WinApp* winApp = new WinApp(600, 600);
	Input* input = new Input(winApp);
	input->KeybordInit();
	DrawGraphs* draw = new DrawGraphs(winApp);
	OutputDebugStringA("test");
	HRESULT result = S_OK;
	XMFLOAT3 vertices[] =
	{
		{-0.5f,-0.5f,0.f},
		{-0.5f,+0.5f,0.f},
		{+0.5f,-0.5f,0.f},
	};

	draw->Init(*vertices);

	//�w�i�F�̐ݒ�
	winApp->SetBackColor(100, 100, 150, 0);

	////Draw--------------------
	//D3D12_HEAP_PROPERTIES heapProp{};   // �q�[�v�ݒ�
	//D3D12_RESOURCE_DESC resDesc{};
	//UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));
	//heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	//// ���\�[�X�ݒ�
	//resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	//resDesc.Height = 1;
	//resDesc.DepthOrArraySize = 1;
	//resDesc.MipLevels = 1;
	//resDesc.SampleDesc.Count = 1;
	//resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//// ���_�o�b�t�@�̐���
	//ID3D12Resource* vertBuff = nullptr;
	//result = winApp->GetDevice()->CreateCommittedResource(
	//	&heapProp, // �q�[�v�ݒ�
	//	D3D12_HEAP_FLAG_NONE,
	//	&resDesc, // ���\�[�X�ݒ�
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&vertBuff));
	//assert(SUCCEEDED(result));

	//// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	//XMFLOAT3* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//assert(SUCCEEDED(result));
	//// �S���_�ɑ΂���
	//for (int i = 0; i < _countof(vertices); i++) {
	//	vertMap[i] = vertices[i]; // ���W���R�s�[
	//}
	//// �q���������
	//vertBuff->Unmap(0, nullptr);

	//// ���_�o�b�t�@�r���[�̍쐬
	//D3D12_VERTEX_BUFFER_VIEW vbView{};
	//// GPU���z�A�h���X
	//vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//// ���_�o�b�t�@�̃T�C�Y
	//vbView.SizeInBytes = sizeVB;
	//// ���_1���̃f�[�^�T�C�Y
	//vbView.StrideInBytes = sizeof(XMFLOAT3);

	//ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	//ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	//ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	//// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	//result = D3DCompileFromFile(
	//	L"BasicVS.hlsl", // �V�F�[�_�t�@�C����
	//	nullptr,
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
	//	"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
	//	D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
	//	0,
	//	&vsBlob, &errorBlob);
	//// �G���[�Ȃ�
	//if (FAILED(result)) {
	//	// errorBlob����G���[���e��string�^�ɃR�s�[
	//	std::string error;
	//	error.resize(errorBlob->GetBufferSize());
	//	std::copy_n((char*)errorBlob->GetBufferPointer(),
	//		errorBlob->GetBufferSize(),
	//		error.begin());
	//	error += "\n";
	//	// �G���[���e���o�̓E�B���h�E�ɕ\��
	//	OutputDebugStringA(error.c_str());
	//	assert(0);
	//}
	//// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	//result = D3DCompileFromFile(
	//	L"BasicPS.hlsl", // �V�F�[�_�t�@�C����
	//	nullptr,
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
	//	"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
	//	D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
	//	0,
	//	&psBlob, &errorBlob);
	//// �G���[�Ȃ�
	//if (FAILED(result)) {
	//	// errorBlob����G���[���e��string�^�ɃR�s�[
	//	std::string error;
	//	error.resize(errorBlob->GetBufferSize());
	//	std::copy_n((char*)errorBlob->GetBufferPointer(),
	//		errorBlob->GetBufferSize(),
	//		error.begin());
	//	error += "\n";
	//	// �G���[���e���o�̓E�B���h�E�ɕ\��
	//	OutputDebugStringA(error.c_str());
	//	assert(0);
	//}
	//// ���_���C�A�E�g
	//D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	//{
	//"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
	//D3D12_APPEND_ALIGNED_ELEMENT,
	//D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	//},
	//};

	//// �O���t�B�b�N�X�p�C�v���C���ݒ�
	//D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	//// �V�F�[�_�[�̐ݒ�
	//pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	//pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	//pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	//pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	//// �T���v���}�X�N�̐ݒ�
	//pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	//// ���X�^���C�U�̐ݒ�
	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �J�����O���Ȃ�
	//pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; // �|���S�����h��Ԃ�
	//pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	//// �u�����h�X�e�[�g
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask
	//	= D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

	//// ���_���C�A�E�g�̐ݒ�
	//pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	//pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	//// �}�`�̌`��ݒ�
	//pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//// ���̑��̐ݒ�
	//pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	//pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	//pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O


	//// ���[�g�V�O�l�`��
	//ID3D12RootSignature* rootSignature;
	//// ���[�g�V�O�l�`���̐ݒ�
	//D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	//rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	//// ���[�g�V�O�l�`���̃V���A���C�Y
	//ID3DBlob* rootSigBlob = nullptr;
	//result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
	//	&rootSigBlob, &errorBlob);
	//assert(SUCCEEDED(result));
	//result = winApp->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
	//	IID_PPV_ARGS(&rootSignature));
	//assert(SUCCEEDED(result));
	//rootSigBlob->Release();
	//// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	//pipelineDesc.pRootSignature = rootSignature;// ���[�g�V�O�l�`��

	//// �p�C�v�����X�e�[�g�̐���
	//ID3D12PipelineState* pipelineState = nullptr;
	//result = winApp->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	//assert(SUCCEEDED(result));
	////DrawEnd-----------------------------------------------

	while (1)
	{
		winApp->PreUpdate();
		input->keybordUpdate();

		////DrawUpdate------------------
		//// �r���[�|�[�g�ݒ�R�}���h
		//D3D12_VIEWPORT viewport{};
		//viewport.Width = winApp->GetWinWidth();
		//viewport.Height = winApp->GetWinHeight();
		//viewport.TopLeftX = 0;
		//viewport.TopLeftY = 0;
		//viewport.MinDepth = 0.0f;
		//viewport.MaxDepth = 1.0f;
		//// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		//winApp->cmdList_->RSSetViewports(1, &viewport);

		//// �V�U�[��`
		//D3D12_RECT scissorRect{};
		//scissorRect.left = 0; // �؂蔲�����W��
		//scissorRect.right = scissorRect.left + winApp->GetWinWidth(); // �؂蔲�����W�E
		//scissorRect.top = 0; // �؂蔲�����W��
		//scissorRect.bottom = scissorRect.top + winApp->GetWinHeight(); // �؂蔲�����W��
		//// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		//winApp->cmdList_->RSSetScissorRects(1, &scissorRect);

		//// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		//winApp->cmdList_->SetPipelineState(pipelineState);
		//winApp->cmdList_->SetGraphicsRootSignature(rootSignature);

		//// �v���~�e�B�u�`��̐ݒ�R�}���h
		//winApp->cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
		//// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
		//winApp->cmdList_->IASetVertexBuffers(0, 1, &vbView);
		//// �`��R�}���h
		//winApp->cmdList_->DrawInstanced(_countof(vertices), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
		//if (PeekMessage(&winApp->msg, nullptr, 0, 0, PM_REMOVE)) {
		//	TranslateMessage(&winApp->msg);
		//	DispatchMessage(&winApp->msg);
		//}

		////��`�؂蔲��
		////D3D12_RECT scissorRect{};
		//scissorRect.left = winApp->GetWinWidth() / 2;
		//scissorRect.right = winApp->GetWinWidth();
		//scissorRect.top = 0;
		//scissorRect.bottom = winApp->GetWinHeight();

		//winApp->cmdList_->RSSetScissorRects(1, &scissorRect);

		////DrawUpdateEnd-----------------------

		//// �r���[�|�[�g�ݒ�R�}���h
		//D3D12_VIEWPORT viewport{};
		//viewport.Width = winApp->GetWinWidth();
		//viewport.Height = winApp->GetWinHeight();
		//viewport.TopLeftX = 0;
		//viewport.TopLeftY = 0;
		//viewport.MinDepth = 0.0f;
		//viewport.MaxDepth = 1.0f;
		//// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		//winApp->cmdList_->RSSetViewports(1, &viewport);

		draw->Update();
		// ������0�L�[��������Ă�����
		if (input->key[DIK_0])
		{
			OutputDebugStringA("Hit 0\n");  // �o�̓E�B���h�E�ɁuHit 0�v�ƕ\��
		}

		winApp->PostUpdate();

		//�����A�v���P�[�V�������I�����Ď���message��WM_QUIT�ɂȂ�
		if (winApp->msg.message == WM_QUIT) {
			break;
		}
	}
	delete winApp;
	delete input;
	delete draw;
	return 0;
}