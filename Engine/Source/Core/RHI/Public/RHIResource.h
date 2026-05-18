#pragma once

#include "Common/RHI_API.h"
#include "Common/RHIResourceType.h"
#include <string>
#include <memory>

#ifndef RHI_ENABLE_RESOURCE_INFO
    #ifdef _DEBUG
        #define RHI_ENABLE_RESOURCE_INFO 1   // Debug: Run
    #else
        #define RHI_ENABLE_RESOURCE_INFO 0   // Release: Close
    #endif
#endif

namespace RHI
{  
    struct GPUVRamAllocation
    {
        GPUVRamAllocation() = default;
        GPUVRamAllocation(uint64_t InAllocationStart, uint64_t InAllocationSize)
            : AllocationStart(InAllocationStart)
            , AllocationSize(InAllocationSize)
        {
        }

        bool IsValid() const { return AllocationSize > 0; }
        
        // in bytes
        uint64_t AllocationStart{};
        // in bytes
        uint64_t AllocationSize{};
    };

    struct RHIResourceInfo
    {
        std::string Name;
        RHIResourceType Type{ RRT_None };
        GPUVRamAllocation VRamAllocation;
        bool IsTransient{ false };
        bool bValid{ true };
        bool bResident{ true };
    };

    /** The base type of RHI resources. */
    class RHI_API RHIResource : public std::enable_shared_from_this<RHIResource>
    {
    public:
        explicit RHIResource(RHIResourceType InType) : Type(InType) {}
        virtual ~RHIResource() = default;

        RHIResource(const RHIResource&) = delete;
        RHIResource& operator=(const RHIResource&) = delete;

        RHIResourceType GetType() const { return Type; }

#if RHI_ENABLE_RESOURCE_INFO
        virtual void GetInfo(RHIResourceInfo& OutInfo) const;
#endif

        // get shared_ptr
        std::shared_ptr<RHIResource> GetSharedPtr()
        {
            return shared_from_this();
        }

    protected:
        RHIResourceType Type;
    };

    struct RHIDescriptorHandle
    {
        RHIDescriptorHandle() = default;
        RHIDescriptorHandle(RHIDescriptorHeapType InType, uint32_t InIndex)
            : Index(InIndex)
            , Type((uint8_t)InType)
        {
        }
        RHIDescriptorHandle(uint8_t InType, uint32_t InIndex)
            : Index(InIndex)
            , Type(InType)
        {
        }

        inline uint32_t                 GetIndex() const { return Index; }
        inline RHIDescriptorHeapType GetType() const { return (RHIDescriptorHeapType)Type; }
        inline uint8_t                  GetRawType() const { return Type; }

        inline bool IsValid() const { return Index != MAX_uint32_t && Type != (uint8_t)RHIDescriptorHeapType::Invalid; }

    private:
        uint32_t    Index{ MAX_uint32_t };
        uint8_t     Type{ (uint8_t)RHIDescriptorHeapType::Invalid };
    };

    //
    // State blocks
    //

    struct SamplerStateDesc // 采样器状态描述符
    {
        SamplerFilter Filter = SamplerFilter::Bilinear;
        SamplerAddressMode AddressU = SamplerAddressMode::Wrap;
        SamplerAddressMode AddressV = SamplerAddressMode::Wrap;
        SamplerAddressMode AddressW = SamplerAddressMode::Wrap;
        float MipLODBias = 0.0f;
        uint32_t MaxAnisotropy = 1;
        SamplerComparisonFunc ComparisonFunc = SamplerComparisonFunc::Never;
        float BorderColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float MinLOD = 0.0f;
        float MaxLOD = 3.402823466e+38f;
    };

    class RHISamplerState : public RHIResource 
    {
    public:
        RHISamplerState(const RHIDescriptorHandle& InHandle) 
            : RHIResource(RRT_SamplerState), Handle(InHandle) {}
        virtual ~RHISamplerState() = default;
        
        virtual bool IsImmutable() const { return false; }
        virtual RHIDescriptorHandle GetBindlessHandle() const { return Handle; }

        protected:
            RHIDescriptorHandle Handle;
    };


} // namespace RHI