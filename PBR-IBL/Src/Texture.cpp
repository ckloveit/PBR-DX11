#include "Texture.h"
#include "DDSTextureLoader.h"
#include <sstream>
#include <filesystem>

using namespace DirectX;

Texture::Texture() = default;

Texture::~Texture()
{
	if (_pTexture)
	{
		_pTexture->Release();
		_pTexture = nullptr;
	}

	if (_pTextureSrv)
	{
		_pTextureSrv->Release();
		_pTextureSrv = nullptr;
	}
}

std::wstring StringToWstring(const std::string& str /*= CP_ACP*/)
{
	std::wstring wstr;
	int len = MultiByteToWideChar(0, 0, str.c_str(), (int)strlen(str.c_str()), NULL, 0);
	wchar_t* m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(0, 0, str.c_str(), (int)strlen(str.c_str()), m_wchar, len);
	m_wchar[len] = '\0';
	wstr = m_wchar;
	delete m_wchar;
	return wstr;
}

bool Texture::Initialise(ID3D11Device* device, const std::string& fileName)
{
	std::string relPath = std::string(fileName);
	std::wstringstream str;

	// Since we're running DirectX, we don't have to worry about the lack of cross-platform for this API:
	const HMODULE module = GetModuleHandle(nullptr);
	if (module != nullptr)
	{
		std::string filepath = std::filesystem::current_path().generic_string();

		/*
		WCHAR exePath[MAX_PATH];
		GetModuleFileName(module, exePath, (sizeof(exePath)));
		const std::wstring::size_type pos = std::wstring(exePath).find_last_of(L"\\/");
		str << std::wstring(exePath).substr(0, pos);
		str << "\\";
		str << relPath;
		*/
		relPath = filepath + "/" + relPath;
	}
	else
	{
		return false;
	}
	std::wstring finalPath = StringToWstring(relPath);
	// Load the texture in.
	ID3D11Resource* texture;
	const HRESULT result = CreateDDSTextureFromFile(device, finalPath.c_str(), &texture, &_pTextureSrv);
	if (FAILED(result))
	{
		return false;
	}

	_pTexture = static_cast<ID3D11Texture2D*>(texture);

	return true;
}

bool Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& fileName)
{
	const std::shared_ptr<Image>& image = Image::fromFile(fileName);
	DXGI_FORMAT format;
	if (!image->isHDR() && image->channels() == 4)
	{
		format = DXGI_FORMAT_R8G8B8A8_UNORM;
	}
	if (image->isHDR() && image->channels() == 4)
	{
		format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	}
	m_width = image->width();
	m_height = image->height();
	m_levels = 0;

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = m_width;
	desc.Height = m_height;
	desc.MipLevels = m_levels;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	/*
	if (m_levels == 0) {
		desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}*/

	if (FAILED(device->CreateTexture2D(&desc, nullptr, &_pTexture))) {
		throw std::runtime_error("Failed to create 2D texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;
	if (FAILED(device->CreateShaderResourceView(_pTexture, &srvDesc, &_pTextureSrv))) {
		throw std::runtime_error("Failed to create 2D texture SRV");
	}

	deviceContext->UpdateSubresource(_pTexture, 0, nullptr, image->pixels<void>(), image->pitch(), 0);
	
	return true;
}

ID3D11Texture2D* Texture::GetTexture() const
{
	return _pTexture;
}

ID3D11ShaderResourceView* Texture::GetSRV() const
{
	return _pTextureSrv;
}
