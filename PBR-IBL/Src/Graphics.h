#pragma once

#include <vector>
#include <DirectXMath.h>

const bool FullScreen = false;
const bool VsyncEnabled = true;
const float ScreenDepth = 1000.0f;
const float ScreenNear = 0.1f;

struct HWND__;
class Input;
class Model;
class PBRShader;
class D3D;
class Camera;
class Skybox;
class FrameCBuffer;
class Texture;
class ObjectCBuffer;

struct PosUvVertexType
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 Uv;
};

struct FullVertexType
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT4 Colour;
	DirectX::XMFLOAT2 Uv;
};

struct MeshData
{
	PosUvVertexType* PosUvVertexData;
	FullVertexType* FullVertexData;
	unsigned long* IndexData;
};

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialise(int screenWidth, int screenHeight, HWND__* hwnd, Input* input);
	bool Frame() const;
	bool Render() const;

private:
	D3D* _pD3D = nullptr;
	Camera* _pCamera = nullptr;
	Skybox* _pSkybox = nullptr;
	FrameCBuffer* _pFrameBuffer = nullptr;
	ObjectCBuffer* _pObjectBuffer = nullptr;
	std::vector<Model*> _pModels;
	PBRShader* _pPBRShader = nullptr;
	Texture* _pNormal = nullptr;
	Texture* _pRoughness = nullptr;
	Texture* _pMetallic = nullptr;
	Input* _pInput = nullptr;
};
