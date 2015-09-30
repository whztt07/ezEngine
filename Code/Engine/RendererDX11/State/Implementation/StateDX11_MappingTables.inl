
static D3D11_CULL_MODE GALCullModeToDX11[ezGALCullMode::ENUM_COUNT] = 
{
  D3D11_CULL_NONE,
  D3D11_CULL_FRONT,
  D3D11_CULL_BACK
};

static const D3D11_TEXTURE_ADDRESS_MODE GALTextureAddressModeToDX11[ezGALTextureAddressMode::ENUM_COUNT] =
{
  D3D11_TEXTURE_ADDRESS_WRAP,
  D3D11_TEXTURE_ADDRESS_MIRROR,
  D3D11_TEXTURE_ADDRESS_CLAMP,
  D3D11_TEXTURE_ADDRESS_BORDER,
  D3D11_TEXTURE_ADDRESS_MIRROR_ONCE
};

static const D3D11_COMPARISON_FUNC GALCompareFuncToDX11[ezGALCompareFunc::ENUM_COUNT] =
{
  D3D11_COMPARISON_NEVER,
  D3D11_COMPARISON_LESS,
  D3D11_COMPARISON_EQUAL,
  D3D11_COMPARISON_LESS_EQUAL,
  D3D11_COMPARISON_GREATER,
  D3D11_COMPARISON_NOT_EQUAL,
  D3D11_COMPARISON_GREATER_EQUAL,
  D3D11_COMPARISON_ALWAYS
};

static const D3D11_FILTER GALFilterTableIndexToDX11[16] =
{
  D3D11_FILTER_MIN_MAG_MIP_POINT,
  D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
  D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
  D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,
  D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,
  D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
  D3D11_FILTER_MIN_MAG_MIP_LINEAR,
  D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
  D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
  D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
  D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
  D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
  D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
  D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR
};

static const D3D11_STENCIL_OP GALStencilOpTableIndexToDX11[8] =
{
  D3D11_STENCIL_OP_KEEP,
  D3D11_STENCIL_OP_ZERO,
  D3D11_STENCIL_OP_REPLACE,
  D3D11_STENCIL_OP_INCR_SAT,
  D3D11_STENCIL_OP_DECR_SAT,
  D3D11_STENCIL_OP_INVERT,
  D3D11_STENCIL_OP_INCR,
  D3D11_STENCIL_OP_DECR
};
