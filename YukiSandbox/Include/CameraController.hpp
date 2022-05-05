/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 */

#pragma once

#include <YukiEntity/Entity.hpp>
#include <YukiUtil/YukiUtilities.hpp>

using Yuki::Utils::isKeyReleased;
using Yuki::Core::KeyCode;

class CameraController : virtual public Yuki::Entity::YukiEntity
{
protected:
  Yuki::SharedPtr<Yuki::Comp::IYukiCamera>     pCamera;
  Yuki::SharedPtr<Yuki::Core::IYukiInpControl> pInpControl;

public:
  explicit CameraController(const Yuki::String& name);
  ~CameraController() override;

  void OnCreate() override;
  void OnAwake() override;
  void OnUpdate() override;
  void OnRender() override;
  void OnDestroy() override;

  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> getInstance();
};


inline void CameraController::OnCreate()
{
  pCamera     = Yuki::Core::GetYukiApp()->GetCurrentScene()->GetCamera();
  pInpControl = Yuki::Core::GetYukiApp()->GetInputController();
}

inline void CameraController::OnAwake()
{
}

inline void CameraController::OnUpdate()
{
  if (!isKeyReleased(KeyCode::KEY_D))
  {
    Yuki::Utils::moveCameraRight(pCamera, 0.01f);
  }
  if (!isKeyReleased(KeyCode::KEY_A))
  {
    Yuki::Utils::moveCameraLeft(pCamera, 0.01f);
  }
  if (!isKeyReleased(KeyCode::KEY_W))
  {
    Yuki::Utils::moveCameraFront(pCamera, 0.01f);
  }
  if (!isKeyReleased(KeyCode::KEY_S))
  {
    Yuki::Utils::moveCameraBack(pCamera, 0.01f);
  }
  if (!isKeyReleased(KeyCode::KEY_Q))
  {
    Yuki::Utils::moveCameraUp(pCamera, 0.01f);
  }
  if (!isKeyReleased(Yuki::Core::KeyCode::KEY_E))
  {
    Yuki::Utils::moveCameraDown(pCamera, 0.01f);
  }
}

inline void CameraController::OnRender()
{
}

inline void CameraController::OnDestroy()
{
}

inline CameraController::CameraController(const Yuki::String& name)
    : Yuki::Entity::YukiEntity(name)
{
}

inline CameraController::~CameraController() = default;

inline Yuki::SharedPtr<Yuki::Entity::YukiEntity> CameraController::getInstance()
{
  static Yuki::SharedPtr<Yuki::Entity::YukiEntity> instance;
  if (!instance.get())
  {
    instance = Yuki::Core::CreateInterfaceInstance<Yuki::Entity::YukiEntity, CameraController>("camera_controller");
  }
  return instance;
}