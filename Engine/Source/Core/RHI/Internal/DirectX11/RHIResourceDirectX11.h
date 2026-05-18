#pragma once
#include <d3d11.h>
#include "RHIResource.h"

#include <wrl.h> // ComPtr
using Microsoft::WRL::ComPtr;

namespace RHI
{
    class SamplerStateDirectX11 : public RHISamplerState
    {
    public:
        SamplerStateDirectX11(ID3D11SamplerState* pSamplerState) : m_pSamplerState(pSamplerState),
         RHISamplerState({RHIDescriptorHeapType::Sampler, 0}) {}
        ~SamplerStateDirectX11() override = default;

        ID3D11SamplerState* GetSamplerState() const { return m_pSamplerState.Get(); }

    private:
        ComPtr<ID3D11SamplerState> m_pSamplerState;
    };
}
