#include "DirectX11/RHIDirectX11.h"
#include "DirectX11/RHIResourceDirectX11.h"
#include "DirectXHelper.h"

namespace RHI
{
    namespace
    {
        D3D11_FILTER ConvertFilter(SamplerFilter filter)
        {
            switch (filter)
            {
            case SamplerFilter::Point:
                return D3D11_FILTER_MIN_MAG_MIP_POINT;
            case SamplerFilter::Bilinear:
                return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            case SamplerFilter::Trilinear:
                return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            case SamplerFilter::Anisotropic:
                return D3D11_FILTER_ANISOTROPIC;
            default:
                return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            }
        }

        D3D11_TEXTURE_ADDRESS_MODE ConvertAddressMode(SamplerAddressMode mode)
        {
            switch (mode)
            {
            case SamplerAddressMode::Wrap:
                return D3D11_TEXTURE_ADDRESS_WRAP;
            case SamplerAddressMode::Mirror:
                return D3D11_TEXTURE_ADDRESS_MIRROR;
            case SamplerAddressMode::Clamp:
                return D3D11_TEXTURE_ADDRESS_CLAMP;
            case SamplerAddressMode::Border:
                return D3D11_TEXTURE_ADDRESS_BORDER;
            case SamplerAddressMode::MirrorOnce:
                return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
            default:
                return D3D11_TEXTURE_ADDRESS_WRAP;
            }
        }

        D3D11_COMPARISON_FUNC ConvertComparisonFunc(SamplerComparisonFunc func)
        {
            switch (func)
            {
            case SamplerComparisonFunc::Never:
                return D3D11_COMPARISON_NEVER;
            case SamplerComparisonFunc::Less:
                return D3D11_COMPARISON_LESS;
            case SamplerComparisonFunc::Equal:
                return D3D11_COMPARISON_EQUAL;
            case SamplerComparisonFunc::LessEqual:
                return D3D11_COMPARISON_LESS_EQUAL;
            case SamplerComparisonFunc::Greater:
                return D3D11_COMPARISON_GREATER;
            case SamplerComparisonFunc::NotEqual:
                return D3D11_COMPARISON_NOT_EQUAL;
            case SamplerComparisonFunc::GreaterEqual:
                return D3D11_COMPARISON_GREATER_EQUAL;
            case SamplerComparisonFunc::Always:
                return D3D11_COMPARISON_ALWAYS;
            default:
                return D3D11_COMPARISON_NEVER;
            }
        }
    }

    std::shared_ptr<RHISamplerState> RHIDirectX11::CreateSamplerState(const SamplerStateDesc& desc)
    {
        D3D11_SAMPLER_DESC samplerDesc = {};
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

        ComPtr<ID3D11SamplerState> pSamplerState;
        ThrowIfFailed(m_pDevice->CreateSamplerState(&samplerDesc, pSamplerState.GetAddressOf()));

        return std::make_shared<SamplerStateDirectX11>(pSamplerState.Get());
    }

    void RHIDirectX11::DeleteSamplerState(std::shared_ptr<RHI::RHISamplerState>& samplerState)
    {
        samplerState.reset();
    }
}
