/**
 * @file methods/kruskal_method.cpp
 * @author [your name]
 *
 * Серверная часть алгоритма Крускала.
 */

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <weighted_graph.hpp>
#include <kruskal.hpp>

using graph::WeightedGraph;

namespace graph {

/**
 * @brief Метод алгоритма Крускала.
 *
 * @param input Входные данные в формате JSON.
 * @param output Выходные данные в формате JSON.
 * @return Функция возвращает 0 в случае успеха и отрицательное число
 * если входные данные заданы некорректно.
 *
 * Функция запускает алгоритм Крускала, используя входные данные
 * в JSON формате. Результат также выдаётся в JSON формате.
 */
int KruskalMethod(const nlohmann::json& input,
    nlohmann::json* output) {
  std::string graphType = input.at("graph_type");
  if (graphType != "WeightedGraph") {
    return -1;
  }

  std::string weightType = input.at("weight_type");
  if (weightType != "int") {
    return -1;
  }

  WeightedGraph<int> graph;

  for (auto& vertex : input.at("vertices")) {
    graph.AddVertex(vertex);
  }

  for (auto& edge : input.at("edges")) {
    graph.AddEdge(edge.at("from"),
                  edge.at("to"),
                  edge.at("weight"));
  }

  auto result = Kruskal(graph);

  int cost = 0;
  for (size_t i = 0; i < result.size(); i++) {
    (*output)["result"][i]["from"] = result[i].from;
    (*output)["result"][i]["to"] = result[i].to;
    (*output)["result"][i]["weight"] = result[i].weight;
    cost += result[i].weight;
  }
  (*output)["cost"] = cost;

  return 0;
}

}  // namespace graph
