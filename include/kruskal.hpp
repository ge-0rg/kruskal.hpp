/**
 * @file include/kruskal.hpp
 *
 * Алгоритм Крускала.
 */

#ifndef INCLUDE_KRUSKAL_HPP_
#define INCLUDE_KRUSKAL_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace graph {

/**
 * @brief Ребро графа для алгоритма Крускала.
 */
template<typename WeightType>
struct KruskalEdge {
  size_t from;
  size_t to;
  WeightType weight;
};

/**
 * @brief Алгоритм Крускала.
 *
 * @param graph Взвешенный граф.
 * @return Минимальное остовное дерево.
 *
 * Функция строит минимальное остовное дерево
 * взвешенного неориентированного графа.
 */
template<typename GraphType>
std::vector<KruskalEdge<typename GraphType::WeightType>> Kruskal(
    const GraphType& graph) {
  using WeightType = typename GraphType::WeightType;

  std::vector<KruskalEdge<WeightType>> edges;

  for (size_t from : graph.Vertices()) {
    for (auto edge : graph.Edges(from)) {
      size_t to = edge.to;
      WeightType weight = edge.weight;

      if (from < to) {
        edges.push_back({from, to, weight});
      }
    }
  }

  std::sort(edges.begin(), edges.end(),
      [](const KruskalEdge<WeightType>& a,
         const KruskalEdge<WeightType>& b) {
        return a.weight < b.weight;
      });

  std::unordered_map<size_t, size_t> tree_id;

  for (size_t vertex : graph.Vertices()) {
    tree_id[vertex] = vertex;
  }

  std::vector<KruskalEdge<WeightType>> result;

  for (const auto& edge : edges) {
    size_t from = edge.from;
    size_t to = edge.to;

    if (tree_id[from] != tree_id[to]) {
      result.push_back(edge);

      size_t old_id = tree_id[to];
      size_t new_id = tree_id[from];

      for (size_t vertex : graph.Vertices()) {
        if (tree_id[vertex] == old_id) {
          tree_id[vertex] = new_id;
        }
      }
    }
  }

  return result;
}

}  // namespace graph

#endif  // INCLUDE_KRUSKAL_HPP_
