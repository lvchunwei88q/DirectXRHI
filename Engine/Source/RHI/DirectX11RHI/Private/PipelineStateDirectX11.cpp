#include "RHIDirectX11.h"

namespace RHI
{
    std::shared_ptr<RHIPipelineState> RHIDirectX11::CreateGraphicsPipelineState(const GraphicsPipelineStateDesc& /*desc*/)
    {
        return nullptr;
    }

    std::shared_ptr<RHIPipelineState> RHIDirectX11::CreateComputePipelineState(const ComputePipelineStateDesc& /*desc*/)
    {
        return nullptr;
    }

    void RHIDirectX11::DeletePipelineState(std::shared_ptr<RHIPipelineState>& pipelineState)
    {
    }
}
