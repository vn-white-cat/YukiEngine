/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiCore/YukiPCH.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThreadPool.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiUtil/YukiChrono.hpp"

namespace Yuki::Core
{

using Chrono::MiliSeconds;

class YukiThreadPool final : virtual public IYukiThreadPool
{
protected:
  SharedPtr<ThreadPoolManager> m_pManager;
  Mutex                        m_PoolMutex;
  Mutex                        m_ActionQueueMutex;
  Vector<Thread>               m_aWorkers;
  ConditionVariable            m_ActionQueueWaiter;
  Queue<CallbackFunc>          m_ActionQueue;
  CallbackFunc                 m_WorkerFunc;
  Atomic<bool>                 m_bPoolActive;
  Atomic<bool>                 m_bPoolStarted;
  Atomic<int>                  m_nNumThreadReady;
  ConditionVariable            m_PoolWaiter;
  bool                         m_bCreateOGLContext;

public:
  YukiThreadPool(int poolSize, bool oglContext);
  ~YukiThreadPool();

  void Start() override;
  void Join() override;
  void PushAction(const CallbackFunc& callback) override;
  void Terminate() override;
  void WaitForPoolReady() override;
  void NotifyWorkers() override;

  Vector<Thread>&      GetWorkers() override;
  ConditionVariable&   GetWorkerWaiter() override;
  Mutex&               GetActionQueueMutex() override;
  Queue<CallbackFunc>& GetActionQueue() override;
  CallbackFunc&        GetWorkerFuncCallback() override;
  bool                 IsPoolActive() override;
  bool                 IsPoolStarted() override;
};

} // namespace Yuki::Core
