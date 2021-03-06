﻿#include <PCH.h>
#include <Foundation/Containers/StaticArray.h>
#include <Foundation/Image/ImageFormat.h>

namespace
{
  struct ezImageFormatMetaData
  {
  public:
    ezImageFormatMetaData() : m_szName("<invalid>"), m_uiBitsPerPixel(0), m_uiRedMask(0), m_uiGreenMask(0), m_uiBlueMask(0), m_uiAlphaMask(0),
      m_formatType(ezImageFormatType::UNKNOWN)
    {}

    ezImageFormatMetaData(const char* name, ezUInt32 uiBitsPerPixel,
                          ezUInt32 uiRedMask, ezUInt32 uiGreenMask,
                          ezUInt32 uiBlueMask, ezUInt32 uiAlphaMask, ezImageFormatType::Enum formatType) :
      m_szName(name), m_uiBitsPerPixel(uiBitsPerPixel),
      m_uiRedMask(uiRedMask), m_uiGreenMask(uiGreenMask),
      m_uiBlueMask(uiBlueMask), m_uiAlphaMask(uiAlphaMask),
      m_formatType(formatType)
    {}

    const char* m_szName;
    ezUInt32 m_uiBitsPerPixel;
    ezUInt32 m_uiRedMask;
    ezUInt32 m_uiGreenMask;
    ezUInt32 m_uiBlueMask;
    ezUInt32 m_uiAlphaMask;
    ezImageFormatType::Enum m_formatType;
  };

  ezStaticArray<ezImageFormatMetaData, ezImageFormat::NUM_FORMATS> s_formatMetaData;
}

static void SetupImageFormatTable()
{
  if (!s_formatMetaData.IsEmpty())
    return;

  s_formatMetaData.SetCountUninitialized(ezImageFormat::NUM_FORMATS);

#define DEFINE_FORMAT(format, bpp, redmask, greenmask, bluemask, alphamask, type) \
  s_formatMetaData[ezImageFormat::format] = ezImageFormatMetaData(#format, bpp, redmask, greenmask, bluemask, alphamask, ezImageFormatType::type)

  DEFINE_FORMAT(UNKNOWN, 0, 0, 0, 0, 0, UNKNOWN);

  DEFINE_FORMAT(R32G32B32A32_TYPELESS, 128, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32B32A32_FLOAT, 128, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32B32A32_UINT, 128, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32B32A32_SINT, 128, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R32G32B32_TYPELESS, 96, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32B32_FLOAT, 96, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32B32_UINT, 96, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32B32_SINT, 96, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R16G16B16A16_TYPELESS, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16B16A16_FLOAT, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16B16A16_UNORM, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16B16A16_UINT, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16B16A16_SNORM, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16B16A16_SINT, 64, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R32G32_TYPELESS, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32_FLOAT, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32_UINT, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32G32_SINT, 64, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R32G8X24_TYPELESS, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(D32_FLOAT_S8X24_UINT, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32_FLOAT_X8X24_TYPELESS, 64, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(X32_TYPELESS_G8X24_UINT, 64, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R10G10B10A2_TYPELESS, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R10G10B10A2_UNORM, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R10G10B10A2_UINT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R10G10B10_XR_BIAS_A2_UNORM, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R11G11B10_FLOAT, 32, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R8G8B8A8_TYPELESS, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, LINEAR);
  DEFINE_FORMAT(R8G8B8A8_UNORM, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, LINEAR);
  DEFINE_FORMAT(R8G8B8A8_UNORM_SRGB, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, LINEAR);
  DEFINE_FORMAT(R8G8B8A8_UINT, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, LINEAR);
  DEFINE_FORMAT(R8G8B8A8_SNORM, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, LINEAR);
  DEFINE_FORMAT(R8G8B8A8_SINT, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, LINEAR);

  DEFINE_FORMAT(B8G8R8A8_UNORM, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000, LINEAR);
  DEFINE_FORMAT(B8G8R8X8_UNORM, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000, LINEAR);
  DEFINE_FORMAT(B8G8R8A8_TYPELESS, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000, LINEAR);
  DEFINE_FORMAT(B8G8R8A8_UNORM_SRGB, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000, LINEAR);
  DEFINE_FORMAT(B8G8R8X8_TYPELESS, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000, LINEAR);
  DEFINE_FORMAT(B8G8R8X8_UNORM_SRGB, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000, LINEAR);

  DEFINE_FORMAT(R16G16_TYPELESS, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16_FLOAT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16_UNORM, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16_UINT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16_SNORM, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16G16_SINT, 32, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R32_TYPELESS, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(D32_FLOAT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32_FLOAT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32_UINT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R32_SINT, 32, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R24G8_TYPELESS, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(D24_UNORM_S8_UINT, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R24_UNORM_X8_TYPELESS, 32, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(X24_TYPELESS_G8_UINT, 32, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(B8G8R8_UNORM, 24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000, LINEAR);

  DEFINE_FORMAT(R8G8_TYPELESS, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8G8_UNORM, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8G8_UINT, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8G8_SNORM, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8G8_SINT, 16, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(B5G6R5_UNORM, 16, 0xF800, 0x07E0, 0x001F, 0x0000, LINEAR);
  DEFINE_FORMAT(B5G5R5A1_UNORM, 16, 0x7C00, 0x03E0, 0x001F, 0x8000, LINEAR);
  DEFINE_FORMAT(B5G5R5X1_UNORM, 16, 0x7C00, 0x03E0, 0x001F, 0x0000, LINEAR);

  DEFINE_FORMAT(R16_TYPELESS, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16_FLOAT, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(D16_UNORM, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16_UNORM, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16_UINT, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16_SNORM, 16, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R16_SINT, 16, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R8_TYPELESS, 8, 0xFF, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8_UNORM, 8, 0xFF, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8_UINT, 8, 0xFF, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8_SNORM, 8, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(R8_SINT, 8, 0, 0, 0, 0, LINEAR);
  DEFINE_FORMAT(A8_UNORM, 8, 0, 0, 0, 0xFF, LINEAR);

  DEFINE_FORMAT(R1_UNORM, 1, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(R9G9B9E5_SHAREDEXP, 32, 0, 0, 0, 0, LINEAR);

  DEFINE_FORMAT(BC1_TYPELESS, 4, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC1_UNORM, 4, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC1_UNORM_SRGB, 4, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC2_TYPELESS, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC2_UNORM, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC2_UNORM_SRGB, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC3_TYPELESS, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC3_UNORM, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC3_UNORM_SRGB, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC4_TYPELESS, 4, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC4_UNORM, 4, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC4_SNORM, 4, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC5_TYPELESS, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC5_UNORM, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC5_SNORM, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC6H_TYPELESS, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC6H_UF16, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC6H_SF16, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC7_TYPELESS, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC7_UNORM, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);
  DEFINE_FORMAT(BC7_UNORM_SRGB, 8, 0, 0, 0, 0, BLOCK_COMPRESSED);

  DEFINE_FORMAT(B4G4R4A4_UNORM, 16, 0x0F00, 0x00F0, 0x000F, 0xF000, LINEAR);
}

static const ezImageFormatMetaData& GetImageFormatMetaData(ezImageFormat::Enum format)
{
  if (s_formatMetaData.IsEmpty())
  {
    SetupImageFormatTable();
  }

  return s_formatMetaData[format];
}

ezUInt32 ezImageFormat::GetBitsPerPixel(Enum format)
{
  return GetImageFormatMetaData(format).m_uiBitsPerPixel;
}

ezImageFormat::Enum ezImageFormat::FromPixelMask(ezUInt32 uiRedMask, ezUInt32 uiGreenMask, ezUInt32 uiBlueMask, ezUInt32 uiAlphaMask, ezUInt32 uiBitsPerPixel)
{
  for (ezUInt32 uiFormat = 0; uiFormat < NUM_FORMATS; uiFormat++)
  {
    Enum format = static_cast<Enum>(uiFormat);
    if (GetRedMask(format) == uiRedMask && GetGreenMask(format) == uiGreenMask && GetBlueMask(format) == uiBlueMask && GetAlphaMask(format) == uiAlphaMask && GetBitsPerPixel(format) == uiBitsPerPixel)
    {
      return format;
    }
  }

  return UNKNOWN;
}

const char* ezImageFormat::GetName(Enum format)
{
  return GetImageFormatMetaData(format).m_szName;
}


ezUInt32 ezImageFormat::GetRedMask(Enum format)
{
  return GetImageFormatMetaData(format).m_uiRedMask;
}

ezUInt32 ezImageFormat::GetGreenMask(Enum format)
{
  return GetImageFormatMetaData(format).m_uiGreenMask;
}

ezUInt32 ezImageFormat::GetBlueMask(Enum format)
{
  return GetImageFormatMetaData(format).m_uiBlueMask;
}

ezUInt32 ezImageFormat::GetAlphaMask(Enum format)
{
  return GetImageFormatMetaData(format).m_uiAlphaMask;
}

ezImageFormatType::Enum ezImageFormat::GetType(Enum format)
{
  return GetImageFormatMetaData(format).m_formatType;
}





EZ_STATICLINK_FILE(Foundation, Foundation_Image_Implementation_ImageFormat);

