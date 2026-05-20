// ========== RHI/Public/RHIDynamicLoader.h ==========

#pragma once
#include <memory>
#include "RHI.h"

namespace RHI
{
    // DLL 导出函数类型定义
    typedef std::unique_ptr<Device> (*PFN_CreateDevice)();
    typedef std::unique_ptr<SwapChain> (*PFN_CreateSwapChain)();
    typedef RHIType (*PFN_GetRHIType)();
}

// 使用宏定义统一函数调用方式
#define CreateDevice_Function     std::unique_ptr<RHI::Device> CreateDevice()
#define CreateSwapChain_Function  std::unique_ptr<RHI::SwapChain> CreateSwapChain()
#define GetRHIType_Function       RHI::RHIType GetRHIType()
