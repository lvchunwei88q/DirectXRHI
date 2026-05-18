#pragma once
#include <d3d12.h>
#include "RHIResource.h"

namespace RHI
{
    class SamplerStateDirectX12 : public RHISamplerState
    {
    public:
        SamplerStateDirectX12(D3D12_SAMPLER_DESC desc, RHIDescriptorHandle handle) 
            : m_SamplerDesc(desc), RHISamplerState(handle) {} // 初始化 Handle

        ~SamplerStateDirectX12() override = default;

        const D3D12_SAMPLER_DESC& GetSamplerDesc() const { return m_SamplerDesc; }

    private:
        D3D12_SAMPLER_DESC m_SamplerDesc;
    };
}
