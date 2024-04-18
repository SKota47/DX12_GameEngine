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

	//背景色の設定
	winApp->SetBackColor(100, 100, 150, 0);

	////Draw--------------------
	//D3D12_HEAP_PROPERTIES heapProp{};   // ヒープ設定
	//D3D12_RESOURCE_DESC resDesc{};
	//UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));
	//heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	//// リソース設定
	//resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//resDesc.Width = sizeVB; // 頂点データ全体のサイズ
	//resDesc.Height = 1;
	//resDesc.DepthOrArraySize = 1;
	//resDesc.MipLevels = 1;
	//resDesc.SampleDesc.Count = 1;
	//resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//// 頂点バッファの生成
	//ID3D12Resource* vertBuff = nullptr;
	//result = winApp->GetDevice()->CreateCommittedResource(
	//	&heapProp, // ヒープ設定
	//	D3D12_HEAP_FLAG_NONE,
	//	&resDesc, // リソース設定
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&vertBuff));
	//assert(SUCCEEDED(result));

	//// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	//XMFLOAT3* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//assert(SUCCEEDED(result));
	//// 全頂点に対して
	//for (int i = 0; i < _countof(vertices); i++) {
	//	vertMap[i] = vertices[i]; // 座標をコピー
	//}
	//// 繋がりを解除
	//vertBuff->Unmap(0, nullptr);

	//// 頂点バッファビューの作成
	//D3D12_VERTEX_BUFFER_VIEW vbView{};
	//// GPU仮想アドレス
	//vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//// 頂点バッファのサイズ
	//vbView.SizeInBytes = sizeVB;
	//// 頂点1つ分のデータサイズ
	//vbView.StrideInBytes = sizeof(XMFLOAT3);

	//ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
	//ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
	//ID3DBlob* errorBlob = nullptr; // エラーオブジェクト

	//// 頂点シェーダの読み込みとコンパイル
	//result = D3DCompileFromFile(
	//	L"BasicVS.hlsl", // シェーダファイル名
	//	nullptr,
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
	//	"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
	//	D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
	//	0,
	//	&vsBlob, &errorBlob);
	//// エラーなら
	//if (FAILED(result)) {
	//	// errorBlobからエラー内容をstring型にコピー
	//	std::string error;
	//	error.resize(errorBlob->GetBufferSize());
	//	std::copy_n((char*)errorBlob->GetBufferPointer(),
	//		errorBlob->GetBufferSize(),
	//		error.begin());
	//	error += "\n";
	//	// エラー内容を出力ウィンドウに表示
	//	OutputDebugStringA(error.c_str());
	//	assert(0);
	//}
	//// ピクセルシェーダの読み込みとコンパイル
	//result = D3DCompileFromFile(
	//	L"BasicPS.hlsl", // シェーダファイル名
	//	nullptr,
	//	D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
	//	"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
	//	D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
	//	0,
	//	&psBlob, &errorBlob);
	//// エラーなら
	//if (FAILED(result)) {
	//	// errorBlobからエラー内容をstring型にコピー
	//	std::string error;
	//	error.resize(errorBlob->GetBufferSize());
	//	std::copy_n((char*)errorBlob->GetBufferPointer(),
	//		errorBlob->GetBufferSize(),
	//		error.begin());
	//	error += "\n";
	//	// エラー内容を出力ウィンドウに表示
	//	OutputDebugStringA(error.c_str());
	//	assert(0);
	//}
	//// 頂点レイアウト
	//D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	//{
	//"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
	//D3D12_APPEND_ALIGNED_ELEMENT,
	//D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	//},
	//};

	//// グラフィックスパイプライン設定
	//D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	//// シェーダーの設定
	//pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	//pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	//pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	//pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	//// サンプルマスクの設定
	//pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	//// ラスタライザの設定
	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // カリングしない
	//pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; // ポリゴン内塗りつぶし
	//pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	//// ブレンドステート
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask
	//	= D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

	//// 頂点レイアウトの設定
	//pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	//pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	//// 図形の形状設定
	//pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//// その他の設定
	//pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	//pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	//pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング


	//// ルートシグネチャ
	//ID3D12RootSignature* rootSignature;
	//// ルートシグネチャの設定
	//D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	//rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	//// ルートシグネチャのシリアライズ
	//ID3DBlob* rootSigBlob = nullptr;
	//result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
	//	&rootSigBlob, &errorBlob);
	//assert(SUCCEEDED(result));
	//result = winApp->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
	//	IID_PPV_ARGS(&rootSignature));
	//assert(SUCCEEDED(result));
	//rootSigBlob->Release();
	//// パイプラインにルートシグネチャをセット
	//pipelineDesc.pRootSignature = rootSignature;// ルートシグネチャ

	//// パイプランステートの生成
	//ID3D12PipelineState* pipelineState = nullptr;
	//result = winApp->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	//assert(SUCCEEDED(result));
	////DrawEnd-----------------------------------------------

	while (1)
	{
		winApp->PreUpdate();
		input->keybordUpdate();

		////DrawUpdate------------------
		//// ビューポート設定コマンド
		//D3D12_VIEWPORT viewport{};
		//viewport.Width = winApp->GetWinWidth();
		//viewport.Height = winApp->GetWinHeight();
		//viewport.TopLeftX = 0;
		//viewport.TopLeftY = 0;
		//viewport.MinDepth = 0.0f;
		//viewport.MaxDepth = 1.0f;
		//// ビューポート設定コマンドを、コマンドリストに積む
		//winApp->cmdList_->RSSetViewports(1, &viewport);

		//// シザー矩形
		//D3D12_RECT scissorRect{};
		//scissorRect.left = 0; // 切り抜き座標左
		//scissorRect.right = scissorRect.left + winApp->GetWinWidth(); // 切り抜き座標右
		//scissorRect.top = 0; // 切り抜き座標上
		//scissorRect.bottom = scissorRect.top + winApp->GetWinHeight(); // 切り抜き座標下
		//// シザー矩形設定コマンドを、コマンドリストに積む
		//winApp->cmdList_->RSSetScissorRects(1, &scissorRect);

		//// パイプラインステートとルートシグネチャの設定コマンド
		//winApp->cmdList_->SetPipelineState(pipelineState);
		//winApp->cmdList_->SetGraphicsRootSignature(rootSignature);

		//// プリミティブ形状の設定コマンド
		//winApp->cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
		//// 頂点バッファビューの設定コマンド
		//winApp->cmdList_->IASetVertexBuffers(0, 1, &vbView);
		//// 描画コマンド
		//winApp->cmdList_->DrawInstanced(_countof(vertices), 1, 0, 0); // 全ての頂点を使って描画
		//if (PeekMessage(&winApp->msg, nullptr, 0, 0, PM_REMOVE)) {
		//	TranslateMessage(&winApp->msg);
		//	DispatchMessage(&winApp->msg);
		//}

		////矩形切り抜き
		////D3D12_RECT scissorRect{};
		//scissorRect.left = winApp->GetWinWidth() / 2;
		//scissorRect.right = winApp->GetWinWidth();
		//scissorRect.top = 0;
		//scissorRect.bottom = winApp->GetWinHeight();

		//winApp->cmdList_->RSSetScissorRects(1, &scissorRect);

		////DrawUpdateEnd-----------------------

		//// ビューポート設定コマンド
		//D3D12_VIEWPORT viewport{};
		//viewport.Width = winApp->GetWinWidth();
		//viewport.Height = winApp->GetWinHeight();
		//viewport.TopLeftX = 0;
		//viewport.TopLeftY = 0;
		//viewport.MinDepth = 0.0f;
		//viewport.MaxDepth = 1.0f;
		//// ビューポート設定コマンドを、コマンドリストに積む
		//winApp->cmdList_->RSSetViewports(1, &viewport);

		draw->Update();
		// 数字の0キーが押されていたら
		if (input->key[DIK_0])
		{
			OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
		}

		winApp->PostUpdate();

		//もうアプリケーションが終わるって時にmessageがWM_QUITになる
		if (winApp->msg.message == WM_QUIT) {
			break;
		}
	}
	delete winApp;
	delete input;
	delete draw;
	return 0;
}