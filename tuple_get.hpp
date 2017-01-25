#ifndef TUPLE_GET_HPP
#define TUPLE_GET_HPP

#include <tuple>
#include <cassert>
#include <utility>

template<typename... T>
struct all_same : std::false_type { };

template<>
struct all_same<> : std::true_type { };

template<typename T>
struct all_same<T> : std::true_type { };

template<typename T, typename... Ts>
struct all_same<T, T, Ts...> : all_same<T, Ts...> { };

template<typename... Ts>
constexpr bool all_same_v = all_same<Ts...>::value;

template<size_t I>
struct get_impl
{
  template<typename T>
  static decltype(auto) get(T& tup, size_t n)
  {
    if (n == I - 1) return std::get<I-1>(tup);
    else return get_impl<I-1>::get(tup, n);
  }
};

template<>
struct get_impl<0>
{
  template<typename T>
  static decltype(auto) get(T& tup, size_t)
  {
    assert(false);
    return std::get<0>(tup);
  }
};

template<typename... Ts, typename std::enable_if_t<all_same_v<Ts...>>* = nullptr>
constexpr decltype(auto) get(std::tuple<Ts...>& tup, int n)
{
  return get_impl<sizeof...(Ts)>::get(tup, n);
}

#endif
