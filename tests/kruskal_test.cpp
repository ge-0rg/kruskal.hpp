/**
 * @file tests/kruskal_test.cpp
 * @author [your name]
 *
 * Тесты для алгоритма graph::Kruskal.
 */

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include "test_core.hpp"

static void EmptyGraphTest(httplib::Client* cli);
static void SimpleTest(httplib::Client* cli);
static void RandomTest(httplib::Client* cli);

void TestKruskal(httplib::Client* cli) {
  TestSuite suite("TestKruskal");
  RUN_TEST_REMOTE(suite, cli, EmptyGraphTest);
  RUN_TEST_REMOTE(suite, cli, SimpleTest);
  RUN_TEST_REMOTE(suite, cli, RandomTest);
}

/**
 * @brief Простейший статический тест для пустого графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void EmptyGraphTest(httplib::Client* cli) {
  nlohmann::json input = R"(
{
  "graph_type": "WeightedGraph",
  "weight_type": "int",
  "vertices": [],
  "edges": []
}
)"_json;

  auto res = cli->Post("/Kruskal", input.dump(), "application/json");
  if (!res) {
    REQUIRE(false);
  }

  nlohmann::json output = nlohmann::json::parse(res->body);
  REQUIRE_EQUAL(static_cast<size_t>(0), output.at("result").size());
}

/**
 * @brief Простейший статический тест.
 *
 * @param cli Указатель на HTTP клиент.
 *
 * Граф: 10-20 (вес 1), 20-30 (вес 2), 30-40 (вес 3), 10-40 (вес 100).
 * Минимальное остовное дерево: рёбра с весами 1, 2, 3. Суммарный вес = 6.
 */
static void SimpleTest(httplib::Client* cli) {
  nlohmann::json input;
  input["graph_type"] = "WeightedGraph";
  input["weight_type"] = "int";
  input["vertices"] = std::vector<size_t>{10, 20, 30, 40};
  input["edges"][0]["from"] = 10;
  input["edges"][0]["to"] = 20;
  input["edges"][0]["weight"] = 1;
  input["edges"][1]["from"] = 20;
  input["edges"][1]["to"] = 30;
  input["edges"][1]["weight"] = 2;
  input["edges"][2]["from"] = 30;
  input["edges"][2]["to"] = 40;
  input["edges"][2]["weight"] = 3;
  input["edges"][3]["from"] = 10;
  input["edges"][3]["to"] = 40;
  input["edges"][3]["weight"] = 100;

  auto res = cli->Post("/Kruskal", input.dump(), "application/json");
  if (!res) {
    REQUIRE(false);
  }

  nlohmann::json output = nlohmann::json::parse(res->body);
  int cost = output.at("cost");
  REQUIRE_EQUAL(6, cost);
  REQUIRE_EQUAL(static_cast<size_t>(3), output.at("result").size());
}

/**
 * @brief Случайный тест.
 *
 * @param cli Указатель на HTTP клиент.
 *
 * Генерирует случайный связный граф на 10 вершинах с произвольными
 * номерами типа size_t из диапазона [100, 1000]. Проверяет, что
 * минимальное остовное дерево содержит ровно N-1 рёбер.
 */
static void RandomTest(httplib::Client* cli) {
  // Число попыток.
  const int numTries = 100;
  // Используется для инициализации генератора случайных чисел.
  std::random_device rd;
  // Генератор случайных чисел.
  std::mt19937 gen(rd());
  // Распределение для вершин графа.
  std::uniform_int_distribution<size_t> vertexId(100, 1000);
  // Распределение для весов рёбер.
  std::uniform_int_distribution<int> weightDist(1, 100);

  for (int it = 0; it < numTries; it++) {
    nlohmann::json input;
    input["graph_type"] = "WeightedGraph";
    input["weight_type"] = "int";

    std::vector<size_t> vertices;
    for (size_t i = 0; i < 10; i++) {
      vertices.push_back(vertexId(gen));
    }

    // Убираем дубликаты вершин.
    std::sort(vertices.begin(), vertices.end());
    vertices.erase(std::unique(vertices.begin(), vertices.end()),
                   vertices.end());

    input["vertices"] = vertices;

    size_t edgeId = 0;

    // Сначала добавляем цепочку, чтобы граф был связным.
    for (size_t i = 1; i < vertices.size(); i++) {
      input["edges"][edgeId]["from"] = vertices[i - 1];
      input["edges"][edgeId]["to"] = vertices[i];
      input["edges"][edgeId]["weight"] = weightDist(gen);
      edgeId++;
    }

    // Затем добавляем произвольные дополнительные рёбра.
    for (size_t i = 0; i < vertices.size(); i++) {
      for (size_t j = i + 1; j < vertices.size(); j++) {
        input["edges"][edgeId]["from"] = vertices[i];
        input["edges"][edgeId]["to"] = vertices[j];
        input["edges"][edgeId]["weight"] = weightDist(gen);
        edgeId++;
      }
    }

    auto res = cli->Post("/Kruskal", input.dump(), "application/json");
    if (!res) {
      REQUIRE(false);
    }

    nlohmann::json output = nlohmann::json::parse(res->body);

    // В остовном дереве должно быть ровно N-1 рёбер.
    if (vertices.size() > 0) {
      REQUIRE_EQUAL(vertices.size() - 1,
                    output.at("result").size());
    }
  }
}
