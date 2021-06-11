#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;
#include "image.hpp"

class Texture
{
public:
	Texture();
	~Texture();

	bool Initialise(ID3D11Device* device, const std::string& fileName);
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& fileName);
	ID3D11Texture2D* GetTexture() const;
	ID3D11ShaderResourceView* GetSRV() const;

private:
	ID3D11Texture2D* _pTexture;
	ID3D11ShaderResourceView* _pTextureSrv;
	int m_width, m_height;
	int m_levels;
};
