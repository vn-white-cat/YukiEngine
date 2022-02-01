#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"

#include "PYukiCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

static volatile unsigned g_CXIndex = 0;

namespace Yuki::Comp
{

YukiCamera::YukiCamera()
    : m_nCamID(g_CXIndex++),
      m_ViewMatrix(1.00f),
      m_ProjectionMatrix(1.00f)
{
  m_CamPos            = {0.00f, 0.00f, -1.00f};
  m_CamDirection      = {0.00f, 0.00f, 1.00f};
  m_CamTop            = {0.00f, 1.00f, 0.00f};
  m_nFOV              = glm::radians(120.00f);
  AutoType windowSize = Core::GetYukiApp()->GetWindow()->GetWindowSize();
  m_nAspectRatio      = windowSize.x / windowSize.y;
  m_nNear             = 0.01f;
  m_nFar              = 1000.00f;
}

YukiCamera::~YukiCamera() = default;

const glm::mat4& YukiCamera::GetCameraViewMatrix()
{
  return m_ViewMatrix;
}

const glm::mat4& YukiCamera::GetCameraProjectionMatrix()
{
  return m_ProjectionMatrix;
}

const glm::vec3& YukiCamera::GetCameraPosition()
{
  return m_CamPos;
}

const glm::vec3& YukiCamera::GetCameraDirection()
{
  return m_CamDirection;
}

const glm::vec3 YukiCamera::GetCameraTopAxis()
{
  return glm::cross(GetCameraHorizontalAxis(), GetCameraVerticalAxis());
}

const glm::vec3 YukiCamera::GetCameraHorizontalAxis()
{
  return glm::cross(GetCameraVerticalAxis(), m_CamTop);
}

const glm::vec3 YukiCamera::GetCameraVerticalAxis()
{
  return m_CamDirection;
}

const float& YukiCamera::GetFieldOfView()
{
  return m_nFOV;
}

const float& YukiCamera::GetViewportAspectRatio()
{
  return m_nAspectRatio;
}

const float& YukiCamera::GetNearPerspective()
{
  return m_nNear;
}

const float& YukiCamera::GetFarPerspective()
{
  return m_nFar;
}

void YukiCamera::CameraRotateViewport(const float& rad)
{
  m_CamTop = glm::rotateZ(m_CamTop, rad);
}

void YukiCamera::CameraRotateDirection(const glm::vec3& rotAxis, const float& rad)
{
  m_CamDirection = glm::rotate(m_CamDirection, rad, rotAxis);
}

void YukiCamera::LookAtPoint(const glm::vec3& point)
{
  m_CamDirection = glm::normalize(point - m_CamPos);
}

void YukiCamera::SetCameraDirection(const glm::vec3& direction)
{
  m_CamDirection = glm::normalize(direction);
}

void YukiCamera::SetCameraPosition(const glm::vec3& position)
{
  m_CamPos = position;
}

void YukiCamera::SetFieldOfView(const float& fov)
{
  m_nFOV = fov;
}

void YukiCamera::SetViewportAspectRatio(const float& ratio)
{
  m_nAspectRatio = ratio;
}

void YukiCamera::SetViewportAspectRatio(const float& width, const float& height)
{
  m_nAspectRatio = width / height;
}

void YukiCamera::SetNearPerspective(const float& pnear)
{
  m_nNear = pnear;
}

void YukiCamera::SetFarPerspective(const float& pfar)
{
  m_nFar = pfar;
}

void YukiCamera::SetCameraKeyCallback(const Core::YukiInpKeyboardCallbackT& callback)
{
  StringStream sstr{};
  sstr << L"Camera Key-control callback " << m_nCamID;
  try
  {
    Core::GetYukiApp()->GetInputController()->RemoveKeyboardInputCallback(sstr.str());
    Core::GetYukiApp()->GetLogger()->PushWarningMessage(L"Replacing old callback");
  }
  catch (Debug::YukiError&)
  {}
  Core::GetYukiApp()->GetInputController()->AddKeyboardInputCallback(sstr.str(), callback);
}

void YukiCamera::SetCameraCursorCallback(const Core::YukiInpCursorCallbackT& callback)
{
  StringStream sstr{};
  sstr << L"Camera Cursor-control callback " << m_nCamID;
  try
  {
    Core::GetYukiApp()->GetInputController()->RemoveCursorInputCallback(sstr.str());
    Core::GetYukiApp()->GetLogger()->PushWarningMessage(L"Replacing old cursor callback");
  }
  catch (Debug::YukiError&)
  {}
  Core::GetYukiApp()->GetInputController()->AddCursorInputCallback(sstr.str(), callback);
}

void YukiCamera::Update()
{
  m_ViewMatrix       = glm::lookAt(m_CamPos, m_CamPos + m_CamDirection, m_CamTop);
  m_ProjectionMatrix = glm::perspective(m_nFOV, m_nAspectRatio, m_nNear, m_nFar);
}

SharedPtr<IYukiCamera> CreateYukiCamera()
{
  return {(IYukiCamera*) new YukiCamera, std::default_delete<IYukiCamera>()};
}

} // namespace Yuki::Comp