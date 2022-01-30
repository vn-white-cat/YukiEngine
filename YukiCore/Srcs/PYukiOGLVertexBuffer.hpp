#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiThread.hpp"
#include "YukiDebug/YukiError.hpp"

namespace Yuki::Core
{

class YukiOGLVertexBuffer : public IYukiOGLVertexBuffer
{
protected:
  unsigned m_nVboID;

public:
  YukiOGLVertexBuffer();
  virtual ~YukiOGLVertexBuffer();

  const unsigned& GetID() override;
  void            BindObject() override;
  bool            OnUse() override;
  void            SetBufferData(std::vector<float>& data) override;
  void            SetBufferData(float* pData, size_t size) override;
  void            Create() override;
  void            Destroy() override;
};

} // namespace Yuki::Core