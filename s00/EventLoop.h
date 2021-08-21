// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#pragma once

#include <thread>

namespace muduo
{

  class EventLoop
  {
  public:
    EventLoop();
    ~EventLoop();

    void loop();

    // 用来断言当前线程为EventLoop被创建的线程
    void assertInLoopThread()
    {
      if (!isInLoopThread())
      {
        abortNotInLoopThread();
      }
    }

    bool isInLoopThread() const { return threadId_ == std::this_thread::get_id(); }

  private:
    void abortNotInLoopThread();
    bool looping_; // 原子
    const std::thread::id threadId_;
  };

}