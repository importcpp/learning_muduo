// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_UTIL_ARENA_H_
#define STORAGE_LEVELDB_UTIL_ARENA_H_

#include <atomic>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace leveldb {
class Arena {

public:
  Arena();
  // 内存池禁止拷贝
  Arena(const Arena &) = delete;
  Arena &operator=(const Arena &) = delete;

  ~Arena();

  // 内存申请，返回指向所申请内存块的指针
  char *Allocate(size_t bytes);

  // 内存统计，记录该对象共申请了多少内存
  size_t MemoryUsage() const { return memory_usage_; }

private:
  char *AllocateNewBlock(size_t block_bytes);

  // 分配状态
  char *alloc_ptr_;
  size_t alloc_bytes_remaining_;

  // Array of new[] allocated memory blocks
  std::vector<char *> blocks_;

  // 内存申请数量统计
  size_t memory_usage_;
};

} // namespace leveldb

#endif // STORAGE_LEVELDB_UTIL_ARENA_H_