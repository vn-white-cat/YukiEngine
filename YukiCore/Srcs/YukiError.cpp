#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiError.hpp"

#define MAKE_ERROR_DEFINATION(__err_name, __err_code)              \
  __err_name## ::__err_name##(const String& file, const int& line) \
      : YukiError(YukiErrCode::__err_code##, file, line)           \
  {}

#define YUKI_CORE_ERROR   L"[YUKI CORE]"
#define YUKI_GLFW_ERROR   L"[GLFW]"
#define YUKI_VULKAN_ERROR L"[VULKAN]"
#define YUKI_GLAD_ERROR   L"[GLAD]"

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
    CHECK_CASE_OF_ERROR(YUKI_LOGGER_CREATE_LOGFILE_ERROR, YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_INSERT_CALLBACK_EXISTS, YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST, YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK, YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_THREAD_ATTACHMENT_DUPLICATE_ID, YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_CREATION_FAILED, YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_THREAD_DETACHMENT_NEXIST, YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(YUKI_SHADER_CODE_BAD_FILE, YUKI_CORE_ERROR);
    CHECK_CASE_OF_ERROR(YUKI_SHADER_CREATE_MODULE_FAILED, YUKI_CORE_ERROR);

    CHECK_CASE_OF_ERROR(GLFW_INITIALIZATION_FAILED, YUKI_GLFW_ERROR);
    CHECK_CASE_OF_ERROR(GLFW_WINDOW_CREATION_FAILED, YUKI_GLFW_ERROR);

    CHECK_CASE_OF_ERROR(GLAD_LOAD_GLLOADER_FAILED, YUKI_GLAD_ERROR);
  }
  return sstr.str();
}

const YukiErrCode& YukiError::getErrorCode() const
{
  return m_ErrCode;
}

MAKE_ERROR_DEFINATION(YukiCreateLogFileError, YUKI_LOGGER_CREATE_LOGFILE_ERROR)

MAKE_ERROR_DEFINATION(YukiInpCtrlInsertCallbackExistsError, YUKI_INPCTRL_INSERT_CALLBACK_EXISTS)
MAKE_ERROR_DEFINATION(YukiInpCtrlRemoveCallbackNExistsError, YUKI_INPCTRL_REMOVE_CALLBACK_NEXIST)
MAKE_ERROR_DEFINATION(YukiInpCtrlInvokeUndefinedCallbackError, YUKI_INPCTRL_INVOKE_UNDEFINED_CALLBACK)

MAKE_ERROR_DEFINATION(YukiThreadAssignmentDuplicateThreadIdError, YUKI_THREAD_ATTACHMENT_DUPLICATE_ID)
MAKE_ERROR_DEFINATION(YukiThreadCreationError, YUKI_THREAD_CREATION_FAILED)
MAKE_ERROR_DEFINATION(YukiThreadDetachmentNotExistError, YUKI_THREAD_DETACHMENT_NEXIST)

MAKE_ERROR_DEFINATION(YukiShaderCodeBadFileError, YUKI_SHADER_CODE_BAD_FILE)
MAKE_ERROR_DEFINATION(YukiShaderCreateModuleError, YUKI_SHADER_CREATE_MODULE_FAILED)

MAKE_ERROR_DEFINATION(YukiGLFWInitError, GLFW_INITIALIZATION_FAILED)
MAKE_ERROR_DEFINATION(YukiWindowCreationError, GLFW_WINDOW_CREATION_FAILED)

MAKE_ERROR_DEFINATION(YukiGladLoadGLLoaderError, GLAD_LOAD_GLLOADER_FAILED)

} // namespace Yuki::Debug