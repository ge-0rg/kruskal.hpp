/**
 * @file methods/methods.hpp
 * @author Mikhail Lozhnikov
 *
 * Объявления серверных частей алгоритмов.
 */

#ifndef METHODS_METHODS_HPP_
#define METHODS_METHODS_HPP_

#include <nlohmann/json.hpp>

namespace graph {

/* Сюда нужно вставить объявление серверной части алгоритма. */

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
    nlohmann::json* output);

/* Конец вставки. */

}  // namespace graph

#endif  // METHODS_METHODS_HPP_
