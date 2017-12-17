#include "stdafx.h"
#include "TextureLoader.h"
#include "Locator.h"


ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	for (auto& it : m_images)
		SafeRelease(&it.second);
}

ID2D1Bitmap * ImageManager::Load(const std::string& name,const std::wstring & filename)
{
	if (m_images[name])
		return m_images[name];
	
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
			hr = Locator::RenderTarget()->CreateBitmapFromWicBitmap(pBitmap, &m_images[name]);
	}
	Assert(hr == S_OK);

	SafeRelease(&pFactory);
	SafeRelease(&pDecoder);
	SafeRelease(&pFrame);
	SafeRelease(&pConverter);
	SafeRelease(&pBitmap);
	
	
	return m_images[name];
}

ID2D1Bitmap * ImageManager::Get(const std::string & name)
{
	if (m_images[name])
		return m_images[name];
	return nullptr;
}
