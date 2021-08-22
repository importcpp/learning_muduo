#include <ctime>
#include <iostream>

#include "arena.h"

namespace leveldb {

void test_memorypool() {
  std::vector<std::pair<size_t, char *>> allocated;
  Arena arena;
  const int N = 10000;
  size_t bytes = 0;
  for (int i = 0; i < N; i++) {
    int s = (i == 0) ? 1 : i;
    char *r;
    r = arena.Allocate(s);

    for (size_t b = 0; b < s; b++) {
      // 对内存地址赋值，方便后面检验
      r[b] = i % 256;
    }

    allocated.push_back(std::make_pair(s, r));
    bytes += s;
    assert(arena.MemoryUsage() > bytes);
  }

  for (size_t i = 0; i < allocated.size(); i++) {
    size_t num_bytes = allocated[i].first;
    const char *p = allocated[i].second;
    for (size_t b = 0; b < num_bytes; b++) {
      // 检验之前的赋值
      if ((int(p[b]) & 0xff) != (i % 256)) {
        std::cout << (int(p[b]) & 0xff) << " " << (i % 256) << std::endl;
        std::cout << (int(p[b]) & 0xff) << " " << (i % 256) << std::endl;
      }
      assert((int(p[b]) & 0xff) == (i % 256));
    }
  }
}

void test_allocate_time() {
  int N = 100000;
  char *p;

  clock_t start_time_without_memory_pool;
  clock_t end_time_without_memory_pool;

  start_time_without_memory_pool = clock();
  for (int i = 1; i < N; ++i) {
    p = new char[i]; // attention: no free
  }
  end_time_without_memory_pool = clock();
  std::cout << "Allocate time without memorypool: "
            << (end_time_without_memory_pool - start_time_without_memory_pool)
            << std::endl;

  Arena arena;

  clock_t start_time_with_memory_pool;
  clock_t end_time_with_memory_pool;
  start_time_with_memory_pool = clock();
  for (int i = 1; i < N; ++i) {
    p = arena.Allocate(i);
  }
  end_time_with_memory_pool = clock();
  std::cout << "Allocate time with memorypool: "
            << (end_time_with_memory_pool - start_time_with_memory_pool)
            << std::endl;
}

} // namespace leveldb

int main(int argc, char **argv) {
  leveldb::test_memorypool();
  leveldb::test_allocate_time();
  return 0;
}