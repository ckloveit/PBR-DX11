#pragma once

struct HWND__;
struct ID3D11DeviceContext;
struct ID3D11Device;
struct ID3D11Buffer;
struct ID3D11Texture2D;
class Texture;
class D3D;
class Cubemap;
class SkyboxShader;
class RectToCubemapShader;
class FrameCBuffer;
class Camera;
class RenderTexture;

class Skybox
{
public:
	Skybox();
	~Skybox();

	bool Initialise(D3D* d3d, HWND__* hwnd, FrameCBuffer* frameBuffer, Camera* camera);
	bool Render(ID3D11DeviceContext* deviceContext, bool bShowDebug) const;

private:
	bool CreateCubeMap(D3D* d3d, HWND__* hwnd);
	void BindMesh(ID3D11DeviceContext* deviceContext) const;

	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;
	Cubemap* _pCubeMap = nullptr;
	Cubemap* _pIrradianceMap = nullptr;
	Cubemap* _pPreFilterMap = nullptr;
	RenderTexture* _pBrdfLUT = nullptr;
	SkyboxShader* _pSkyboxShader = nullptr;
	FrameCBuffer* _pFrameBuffer = nullptr;
	Camera* _pCamera = nullptr;
};
