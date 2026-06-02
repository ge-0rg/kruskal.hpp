#include "kuhn.hpp"

#include "gtest/gtest.h"

#include <vector>

namespace graph {
namespace {

TEST(KuhnTest, SimpleGraph) {
  std::vector<std::vector<int>> g(3);
  g[0] = {0, 1};
  g[1] = {0, 2};
  g[2] = {1};

  std::vector<int> mt = Kuhn(3, 3, g);

  int size = 0;
  for (int i = 0; i < 3; ++i) {
    if (mt[i] != -1) {
      ++size;
    }
  }
  EXPECT_EQ(size, 3);
}

TEST(KuhnTest, EmptyGraph) {
  std::vector<std::vector<int>> g(3);
  std::vector<int> mt = Kuhn(3, 3, g);

  int size = 0;
  for (int i = 0; i < 3; ++i) {
    if (mt[i] != -1) {
      ++size;
    }
  }
  EXPECT_EQ(size, 0);
}

}  // namespace
}  // namespace graph
