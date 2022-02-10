#pragma once

#include "YukiCore/YukiPCH.hpp"

namespace Yuki::Core
{

class YUKIAPI IYukiObject
{
public:
  virtual void Create(){};
  virtual void Awake(){};
  virtual void Update(){};
  virtual void Render(){};
  virtual void Destroy(){};
};

} // namespace Yuki::Core

namespace Yuki
{

namespace Core
{

class YUKIAPI IYukiApp;
class YUKIAPI IYukiGfxControl;
class YUKIAPI IYukiShaderProgram;
class YUKIAPI IYukiWindow;
class YUKIAPI IYukiInpControl;
class YUKIAPI IYukiThread;
class YUKIAPI IYukiOGLObject;
class YUKIAPI IYukiOGLVertexBuffer;
class YUKIAPI IYukiOGLShaderProgram;
class YUKIAPI IYukiOGLElementBuffer;
class YUKIAPI IYukiOGLTexture;

enum class PrimitiveTopology;
enum class TextureType;
enum class TextureMinFilter;
enum class TextureMagFilter;
enum class TextureDepthStencilMode;
enum class TextureCompareFunc;
enum class TextureCompareMode;
enum class PixelBasedInternalFormat;
enum class VertexFlag;
enum class KeyState;
enum class JoyStickHatState;
enum class KeyCode;
enum class MouseBtnCode;
enum class JoystickBtnCode;
enum class GamepadBtnCode;
enum class GamepadAxes;
enum class KeyModifier;

struct StKeyStatus;
struct StVertexFormat;
struct StIndexData;
struct StKeyStatus;

} // namespace Core

namespace Debug
{

enum class YUKIAPI YukiErrCode;

class YUKIAPI YukiError;
class YUKIAPI IYukiLogger;

} // namespace Debug

namespace Chrono
{

struct YUKIAPI StDateTimeFormat;
struct YUKIAPI StAsciiDateTimeFormat;

class YUKIAPI IYukiTimer;

} // namespace Chrono

namespace Comp
{

class YUKIAPI IYukiComp;
class YUKIAPI IYukiMesh;
class YUKIAPI IYukiScene;
class YUKIAPI IYukiCamera;
class YUKIAPI YukiEntity;
class YUKIAPI YukiScene;
class YUKIAPI IYukiDirectionalLight;
class YUKIAPI IYukiPointLight;
class YUKIAPI IYukiFlashLight;

} // namespace Comp

} // namespace Yuki
