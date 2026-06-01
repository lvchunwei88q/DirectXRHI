#include "RHIDirectX11.h"
#include "RHIResourceDirectX11.h"

namespace RHI
{
    RHIDescriptorHandle RHIDirectX11::CreateStandardHeapDescriptorView(RHIBuffer* Buffer,DescriptorRangeType Type)
    {
        Buffer->SetBindlessHandle(RHIDescriptorHandle(RHIDescriptorHeapType::Standard,0));
        return Buffer->GetBindlessHandle();
    }

    RHIDescriptorHandle RHIDirectX11::CreateStandardHeapDescriptorView(RHITexture* Texture,DescriptorRangeType Type)
    {
        return RHIDescriptorHandle();
    }

    RHIDescriptorHandle RHIDirectX11::CreateSamplerHeapDescriptorView(const SamplerStateDesc& /*desc*/)
    {
        return RHIDescriptorHandle();
    }

    RHIDescriptorHandle RHIDirectX11::CreateRTVHeapDescriptorView(RHIRenderTargetView* /*InView*/)
    {
        return RHIDescriptorHandle();
    }

    RHIDescriptorHandle RHIDirectX11::CreateDSVHeapDescriptorView(RHIDepthStencilView* /*InView*/)
    {
        return RHIDescriptorHandle();
    }
}
