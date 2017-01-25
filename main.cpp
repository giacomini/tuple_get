#include "tuple_get.hpp"

int main()
{
  auto t = std::make_tuple(1, 2);

  int n = 1;
  decltype(auto) v = get(t, n);
  v = 3;

  return std::get<1>(t);
}
