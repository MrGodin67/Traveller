#include "stdafx.h"
#include "TextureLoader.h"
#include "Locator.h"
std::unordered_map<std::wstring,ID2D1Bitmap*> TextureLoader::m_images;

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
	for (auto& it : m_images)
		SafeRelease(&it.second);
}

ID2D1Bitmap * TextureLoader::Load(const std::wstring & filename)
{
	if (m_images[filename])
		return m_images[filename];
	
	IWICBitmapDecoder *pDecoder = nullptr;
	IWICBitmapFrameDecode *pFrame = nullptr;
	IWICFormatConverter *pConverter = nullptr;
	IWICBitmap *pBitmap = nullptr;
	IWICImagingFactory *pFactory = nullptr;
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory));

	if (SUCCEEDED(hr))
	{
		hr = pFactory->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ,
			WICDecodeMetadataCacheOnDemand, &pDecoder);
	}
	if (SUCCEEDED(hr))
	{
		pDecoder->GetFrame(0, &pFrame);
	}
	if (SUCCEEDED(hr))
	{

		hr = pFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPRGBA,
			WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom);
	}
	if (SUCCEEDED(hr))
	{
		hr = pFactory->CreateBitmapFromSource(pConverter, WICBitmapCacheOnDemand, &pBitmap);
		

		if (SUCCEEDED(hr))
			hr = Locator::RenderTarget()->CreateBitmapFromWicBitmap(pBitmap, &m_images[filename]);
	}
	Assert(hr == S_OK);

	SafeRelease(&pFactory);
	SafeRelease(&pBitmap);
	SafeRelease(&pDecoder);
	SafeRelease(&pFrame);
	return m_images[filename];
}
