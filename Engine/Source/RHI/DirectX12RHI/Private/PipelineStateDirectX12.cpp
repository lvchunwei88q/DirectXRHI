#include "RHIDirectX12.h"

namespace RHI
{
    std::shared_ptr<RHIPipelineState> RHIDirectX12::CreateGraphicsPipelineState(const GraphicsPipelineStateDesc& /*desc*/)
    {
        return nullptr;
    }

    std::shared_ptr<RHIPipelineState> RHIDirectX12::CreateComputePipelineState(const ComputePipelineStateDesc& /*desc*/)
    {
        return nullptr;
    }

    void RHIDirectX12::DeletePipelineState(std::shared_ptr<RHIPipelineState>& pipelineState)
    {
    }
}
