#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiGraphics.hpp"

namespace Yuki::Core
{

class YukiOGLElementBuffer : public IYukiOGLElementBuffer
{
protected:
  unsigned m_nEboID;
  unsigned m_nElementCount;

public:
  YukiOGLElementBuffer();
  virtual ~YukiOGLElementBuffer();

  const unsigned& GetID() override;
  void            BindObject() override;
  bool            OnUse() override;
  void            SetBufferData(std::vector<unsigned>& data) override;
  void            SetBufferData(unsigned* pData, size_t size) override;
  void            DrawElements(Core::PrimitiveTopology topology, const unsigned& start, const unsigned& count) override;
  void            DrawAllElements(Core::PrimitiveTopology topology) override;
  void            Create() override;
  void            Destroy() override;
};

} // namespace Yuki::Core