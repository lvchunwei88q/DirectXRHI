#include "DirectX12/RHIDirectX12.h"
#include "DirectX12/RHIResourceDirectX12.h"
#include "DirectXHelper.h"

namespace RHI
{
    namespace
    {
        D3D12_FILTER ConvertFilter(SamplerFilter filter)
        {
            switch (filter)
            {
            case SamplerFilter::Point:
                return D3D12_FILTER_MIN_MAG_MIP_POINT;
            case SamplerFilter::Bilinear:
                return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            case SamplerFilter::Trilinear:
                return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
            case SamplerFilter::Anisotropic:
                return D3D12_FILTER_ANISOTROPIC;
            default:
                return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
            }
        }

        D3D12_TEXTURE_ADDRESS_MODE ConvertAddressMode(SamplerAddressMode mode)
        {
            switch (mode)
            {
            case SamplerAddressMode::Wrap:
                return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
            case SamplerAddressMode::Mirror:
                return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
            case SamplerAddressMode::Clamp:
                return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
            case SamplerAddressMode::Border:
                return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
            case SamplerAddressMode::MirrorOnce:
                return D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
            default:
                return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
            }
        }

        D3D12_COMPARISON_FUNC ConvertComparisonFunc(SamplerComparisonFunc func)
        {
            switch (func)
            {
            case SamplerComparisonFunc::Never:
                return D3D12_COMPARISON_FUNC_NEVER;
            case SamplerComparisonFunc::Less:
                return D3D12_COMPARISON_FUNC_LESS;
            case SamplerComparisonFunc::Equal:
                return D3D12_COMPARISON_FUNC_EQUAL;
            case SamplerComparisonFunc::LessEqual:
                return D3D12_COMPARISON_FUNC_LESS_EQUAL;
            case SamplerComparisonFunc::Greater:
                return D3D12_COMPARISON_FUNC_GREATER;
            case SamplerComparisonFunc::NotEqual:
                return D3D12_COMPARISON_FUNC_NOT_EQUAL;
            case SamplerComparisonFunc::GreaterEqual:
                return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
            case SamplerComparisonFunc::Always:
                return D3D12_COMPARISON_FUNC_ALWAYS;
            default:
                return D3D12_COMPARISON_FUNC_NEVER;
            }
        }
    }

    std::shared_ptr<RHISamplerState> RHIDirectX12::CreateSamplerState(const SamplerStateDesc& desc)
    {
        D3D12_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = ConvertFilter(desc.Filter);
        samplerDesc.AddressU = ConvertAddressMode(desc.AddressU);
        samplerDesc.AddressV = ConvertAddressMode(desc.AddressV);
        samplerDesc.AddressW = ConvertAddressMode(desc.AddressW);
        samplerDesc.MipLODBias = desc.MipLODBias;
        samplerDesc.MaxAnisotropy = desc.MaxAnisotropy;
        samplerDesc.ComparisonFunc = ConvertComparisonFunc(desc.ComparisonFunc);
        samplerDesc.BorderColor[0] = desc.BorderColor[0];
        samplerDesc.BorderColor[1] = desc.BorderColor[1];
        samplerDesc.BorderColor[2] = desc.BorderColor[2];
        samplerDesc.BorderColor[3] = desc.BorderColor[3];
        samplerDesc.MinLOD = desc.MinLOD;
        samplerDesc.MaxLOD = desc.MaxLOD;

        uint32_t index = m_SamplerHeapAllocator.Allocate();
        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = GetSamplerCPUHandle(index);

        m_pDevice->CreateSampler(&samplerDesc, cpuHandle);

        RHIDescriptorHandle handle = {(uint8_t)RHIDescriptorHeapType::Sampler, index};

        return std::make_shared<SamplerStateDirectX12>(samplerDesc, handle);
    }

    void RHIDirectX12::DeleteSamplerState(std::shared_ptr<RHI::RHISamplerState>& samplerState) 
    {
        m_SamplerHeapAllocator.Free(samplerState->GetBindlessHandle().GetIndex());
        samplerState.reset();
    }
}