/**
 * @file include/kruskal.hpp
 * @author GEO
 *
 * Алгоритм Крускала для построения минимального остовного дерева.
 */

#ifndef INCLUDE_KRUSKAL_HPP_
#define INCLUDE_KRUSKAL_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace graph {

/**
 * @brief Ребро графа для алгоритма Крускала.
 *
 * @tparam WeightType Тип веса рёбер.
 */
template<typename WeightType>
struct KruskalEdge {
  /// Начало ребра.
  size_t from;
  /// Конец ребра.
  size_t to;
  /// Вес ребра.
  WeightType weight;
};

/**
 * @brief Алгоритм Крускала.
 *
 * @tparam GraphType Тип графа. Должен поддерживать методы Vertices(),
 * Edges() и EdgeWeight(). Должен иметь тип WeightType.
 * @param graph Взвешенный неориентированный граф.
 * @return Список рёбер минимального остовного дерева.
 *
 * Функция строит минимальное остовное дерево взвешенного
 * неориентированного графа. Вершины графа имеют произвольную нумерацию
 * типа size_t, поэтому для хранения компонент связности используется
 * словарь (unordered_map).
 */
template<typename GraphType>
std::vector<KruskalEdge<typename GraphType::WeightType>> Kruskal(
    const GraphType& graph) {
  using WeightType = typename GraphType::WeightType;

  std::vector<KruskalEdge<WeightType>> edges;

  for (size_t from : graph.Vertices()) {
    for (size_t to : graph.Edges(from)) {
      if (from < to) {
        WeightType weight = graph.EdgeWeight(from, to);
        edges.push_back({from, to, weight});
      }
    }
  }

  std::sort(edges.begin(), edges.end(),
      [](const KruskalEdge<WeightType>& a,
         const KruskalEdge<WeightType>& b) {
        return a.weight < b.weight;
      });

  std::unordered_map<size_t, size_t> treeId;
  for (size_t vertex : graph.Vertices()) {
    treeId[vertex] = vertex;
  }

  std::vector<KruskalEdge<WeightType>> result;

  for (const auto& edge : edges) {
    size_t from = edge.from;
    size_t to = edge.to;
    if (treeId[from] != treeId[to]) {
      result.push_back(edge);
      size_t oldId = treeId[to];
      size_t newId = treeId[from];
      for (size_t vertex : graph.Vertices()) {
        if (treeId[vertex] == oldId) {
          treeId[vertex] = newId;
        }
      }
    }
  }

  return result;
}

}  // namespace graph

#endif  // INCLUDE_KRUSKAL_HPP_
