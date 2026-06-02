#ifndef INCLUDE_KUHN_HPP_
#define INCLUDE_KUHN_HPP_

#include <vector>

namespace graph {

std::vector<int> Kuhn(int n, int k,
                      const std::vector<std::vector<int>>& g);

}  // namespace graph

#endif  // INCLUDE_KUHN_HPP_
