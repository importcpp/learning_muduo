// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "EventLoop.h"

#include <assert.h>
#include <poll.h>
#include <iostream>

using namespace muduo;

__thread EventLoop *t_loopInThisThread = 0;

EventLoop::EventLoop()
    : looping_(false),
      threadId_(std::this_thread::get_id())
{
  std::cout << "EventLoop created " << this << " in thread " << threadId_ << std::endl;
  if (t_loopInThisThread)
  {
    std::cerr << "Another EventLoop " << t_loopInThisThread << " exists in this thread " << threadId_ << std::endl;
  }
  else
  {
    t_loopInThisThread = this;
  }
}

EventLoop::~EventLoop()
{
  assert(!looping_);
  t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;

  ::poll(NULL, 0, 5 * 1000);

  std::cout << "EventLoop " << this << " stop looping" << std::endl;
  looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
  std::cerr << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " << std::this_thread::get_id() << std::endl;
  // std::abort();
}
