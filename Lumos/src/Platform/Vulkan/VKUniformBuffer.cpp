#include "lmpch.h"
#include "VKUniformBuffer.h"
#include "VKDevice.h"
#include "VKTools.h"

namespace Lumos
{
	namespace Graphics
	{
		VKUniformBuffer::VKUniformBuffer(uint32_t size, const void* data)
		{
			VKBuffer::Init(vk::BufferUsageFlagBits::eUniformBuffer, size, data);
		}

		VKUniformBuffer::VKUniformBuffer()
		{
		}

		VKUniformBuffer::~VKUniformBuffer()
		{
		}

		void VKUniformBuffer::Init(uint32_t size, const void* data)
		{
			VKBuffer::Init(vk::BufferUsageFlagBits::eUniformBuffer, size, data);
		}

		void VKUniformBuffer::SetData(uint32_t size, const void* data)
		{
			VKBuffer::Map();
			memcpy(m_Mapped, data, static_cast<size_t>(size));
			VKBuffer::UnMap();
		}

		void VKUniformBuffer::SetDynamicData(uint32_t size, uint32_t typeSize, const void* data)
		{
			VKBuffer::Map();
			memcpy(m_Mapped, data, size);
			VKBuffer::Flush(size);
			VKBuffer::UnMap();
		}
        
        void VKUniformBuffer::MakeDefault()
        {
            CreateFunc = CreateFuncVulkan;
            CreateDataFunc = CreateDataFuncVulkan;
        }
        
        UniformBuffer* VKUniformBuffer::CreateDataFuncVulkan(uint32_t size, const void* data)
        {
            return lmnew VKUniformBuffer(size, data);
        }
        
        UniformBuffer* VKUniformBuffer::CreateFuncVulkan()
        {
            return lmnew VKUniformBuffer();
        }
	}
}
