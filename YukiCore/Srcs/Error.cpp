#include "YukiCore/YukiVE.hpp"
#include "YukiCore/Error.hpp"

#define MAKE_ERROR_DEFINATION(__err_name, __err_code)              \
  __err_name## ::__err_name##(const String& file, const int& line) \
      : YukiError(YukiErrCode::__err_code##, file, line)           \
  {}

#define YUKI_GLFW_ERROR   L"[GLFW]"
#define YUKI_VULKAN_ERROR L"[VULKAN]"

#define CHECK_CASE_OF_ERROR(__err_code, __caused_by)                            \
  case YukiErrCode::__err_code##:                                               \
    sstr << __caused_by L" >> " L#__err_code L"<< .Please Check your system\n"; \
    break

namespace Yuki::Debug
{

YukiError::YukiError(const YukiErrCode& code, const String& file, const int& line)
    : std::runtime_error("[RTE]"),
      m_File(file),
      m_nLine(line),
      m_ErrCode(code)
{}

String YukiError::getErrorMessage() const
{
  StringStream sstr = {};
  sstr << "[YUKI ERROR REPORT]\n\t[RTE at file: " << m_File << " - line " << m_nLine << "] -> ";
  switch (m_ErrCode)
  {
    CHECK_CASE_OF_ERROR(GLFW_INITIALIZATION_FAILED, YUKI_GLFW_ERROR);
    CHECK_CASE_OF_ERROR(GLFW_WINDOW_CREATION_FAILED, YUKI_GLFW_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_CREATE_INSTANCE_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_CHECK_VALIDATION_LAYER_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_GETFUNCPTR_CREATE_DEBUG_MESSAGE_FUNC_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_GETFUNCPTR_DESTROY_DEBUG_MESSAGE_FUNC_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_CREATE_DEBUG_MESSENGER_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_NO_SUPPORTED_PHYSICAL_DEVICE_FOUND, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_CREATE_LOGICAL_DEVICE_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_CREATE_WIN32_SURFACE_KHR_FAILED, YUKI_VULKAN_ERROR);
    CHECK_CASE_OF_ERROR(VULKAN_CREATE_SWAPCHAIN_FAILED, YUKI_VULKAN_ERROR);
  }
  return sstr.str();
}

const YukiErrCode& YukiError::getErrorCode() const
{
  return m_ErrCode;
}

MAKE_ERROR_DEFINATION(YukiGLFWInitError, GLFW_INITIALIZATION_FAILED)
MAKE_ERROR_DEFINATION(YukiWindowCreationError, GLFW_WINDOW_CREATION_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanCreateInstanceError, VULKAN_CREATE_INSTANCE_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanValidateLayerError, VULKAN_CHECK_VALIDATION_LAYER_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanGetFuncPtrCreateDebugMessageFuncError, VULKAN_GETFUNCPTR_CREATE_DEBUG_MESSAGE_FUNC_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanCreateDebugMessengerError, VULKAN_CREATE_DEBUG_MESSENGER_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanGetFuncPtrDestroyDebugMessageFuncError, VULKAN_GETFUNCPTR_DESTROY_DEBUG_MESSAGE_FUNC_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanNoSupportedPhysicalDeviceFoundError, VULKAN_NO_SUPPORTED_PHYSICAL_DEVICE_FOUND)
MAKE_ERROR_DEFINATION(YukiVulkanCreateLogicalDeviceError, VULKAN_CREATE_LOGICAL_DEVICE_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanCreateWin32SurfaceKHRError, VULKAN_CREATE_WIN32_SURFACE_KHR_FAILED)
MAKE_ERROR_DEFINATION(YukiVulkanCreateSwapChainError, VULKAN_CREATE_SWAPCHAIN_FAILED)

} // namespace Yuki::Debug