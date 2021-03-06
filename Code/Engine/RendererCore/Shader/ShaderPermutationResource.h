#pragma once

#include <RendererCore/Basics.h>
#include <RendererCore/Shader/ShaderPermutationBinary.h>
#include <RendererCore/ShaderCompiler/PermutationGenerator.h>
#include <Core/ResourceManager/Resource.h>
#include <Core/ResourceManager/ResourceTypeLoader.h>
#include <Foundation/Time/Timestamp.h>

typedef ezTypedResourceHandle<class ezShaderPermutationResource> ezShaderPermutationResourceHandle;
typedef ezTypedResourceHandle<class ezShaderStateResource> ezShaderStateResourceHandle;

struct ezShaderPermutationResourceDescriptor
{
};

class EZ_RENDERERCORE_DLL ezShaderPermutationResource : public ezResource<ezShaderPermutationResource, ezShaderPermutationResourceDescriptor>
{
  EZ_ADD_DYNAMIC_REFLECTION(ezShaderPermutationResource, ezResourceBase);

public:
  ezShaderPermutationResource();

  ezGALShaderHandle GetGALShader() const { return m_hShader; }
  const ezShaderStageBinary* GetShaderStageBinary(ezGALShaderStage::Enum stage) const { return m_pShaderStageBinaries[stage]; }

  ezGALBlendStateHandle GetBlendState() const { return m_hBlendState; }
  ezGALDepthStencilStateHandle GetDepthStencilState() const { return m_hDepthStencilState; }
  ezGALRasterizerStateHandle GetRasterizerState() const { return m_hRasterizerState; }

  bool IsShaderValid() const { return m_bShaderPermutationValid; }

  ezArrayPtr<const ezPermutationVar> GetPermutationVars() const { return m_PermutationVars; }

private:
  virtual ezResourceLoadDesc UnloadData(Unload WhatToUnload) override;
  virtual ezResourceLoadDesc UpdateContent(ezStreamReader* Stream) override;
  virtual void UpdateMemoryUsage(MemoryUsage& out_NewMemoryUsage) override;
  virtual ezResourceTypeLoader* GetDefaultResourceTypeLoader() const override;

private:

  friend class ezShaderManager;

  ezShaderStageBinary* m_pShaderStageBinaries[ezGALShaderStage::ENUM_COUNT];

  bool m_bShaderPermutationValid;
  ezGALShaderHandle m_hShader;

  ezGALBlendStateHandle m_hBlendState;
  ezGALDepthStencilStateHandle m_hDepthStencilState;
  ezGALRasterizerStateHandle m_hRasterizerState;

  ezHybridArray<ezPermutationVar, 16> m_PermutationVars;
};


class ezShaderPermutationResourceLoader : public ezResourceTypeLoader
{
public:

  virtual ezResourceLoadData OpenDataStream(const ezResourceBase* pResource) override;
  virtual void CloseDataStream(const ezResourceBase* pResource, const ezResourceLoadData& LoaderData) override;

  virtual bool IsResourceOutdated(const ezResourceBase* pResource) const override;

private:

  ezResult RunCompiler(const ezResourceBase* pResource, ezShaderPermutationBinary& BinaryInfo, bool bForce);

};