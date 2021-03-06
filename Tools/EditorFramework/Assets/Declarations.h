﻿#pragma once

#include <Foundation/Strings/HashedString.h>
#include <Foundation/Strings/String.h>
#include <Foundation/Types/Uuid.h>
#include <Foundation/Types/Bitflags.h>

class ezImage;
class ezAssetFileHeader;

struct ezAssetExistanceState
{
  enum Enum
  {
    FileAdded,
    FileRemoved,
    FileModified,
    FileUnchanged,
  };
};

struct ezAssetDocumentFlags
{
  typedef ezUInt8 StorageType;

  enum Enum
  {
    None = 0,
    AutoTransformOnSave = EZ_BIT(0),      ///< Every time the document is saved, TransformAsset is automatically executed
    DisableTransform = EZ_BIT(1),         ///< If set, TransformAsset will not do anything
    OnlyTransformManually = EZ_BIT(2),    ///< The asset transformation is not done, unless explicitly requested for this asset
    SupportsThumbnail = EZ_BIT(3),       ///< The asset supports thumbnail generation (InternalCreateThumbnail must be implemented). 
    AutoThumbnailOnTransform = EZ_BIT(4),///< Thumbnail is automatically generated by the asset transform, and does not need to be explicitely created.
    Default = None
  };

  struct Bits
  {
    StorageType AutoTransformOnSave : 1;
    StorageType DisableTransform : 1;
    StorageType OnlyTransformManually : 1;
  };
};

EZ_DECLARE_FLAGS_OPERATORS(ezAssetDocumentFlags);

struct ezSubAssetData
{
  ezUuid m_Guid;
  ezHashedString m_sAssetTypeName;
  ezString m_sName;
};

