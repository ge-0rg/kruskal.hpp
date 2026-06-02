#include "kuhn.hpp"

#include <vector>

namespace graph {

namespace {

bool Dfs(int v, const std::vector<std::vector<int>>& g,
         std::vector<int>* mt, std::vector<bool>* used) {
  if ((*used)[v]) return false;
  (*used)[v] = true;

  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if ((*mt)[to] == -1 || Dfs((*mt)[to], g, mt, used)) {
      (*mt)[to] = v;
      return true;
    }
  }
  return false;
}

}  // namespace

std::vector<int> Kuhn(int n, int k,
                      const std::vector<std::vector<int>>& g) {
  std::vector<int> mt(k, -1);
  std::vector<bool> used(n);

  for (int v = 0; v < n; ++v) {
    used.assign(n, false);
    Dfs(v, g, &mt, &used);
  }

  return mt;
}

}  // namespace graph
