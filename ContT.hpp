#ifndef __CONTT_HPP__
#define __CONTT_HPP__

#include "F.hpp"

template <typename R, template <typename> class M, typename A>
struct ContT {
  F<F<A,M<R>>,M<R>> unContT;
};

template <typename R, template <typename> class M, typename A, typename B>
ContT<R,M,B> map(const F<A,B>& f, const ContT<R,M,A>& ma) {
  ContT<R,M,B> r;
  r.unContT = arr(std::function<M<R>(F<B,M<R>>)>([=](F<B,M<R>> k) {
    return ma.unContT(arr(std::function<M<R>(A)>([=](A a) {
      return call(k, call(f, a));
    })));
  }));
  return r;
}

template <typename R, template <typename> class M, typename A, typename B>
ContT<R,M,B> apply(const ContT<R,M,F<A,B>>& mf, const ContT<R,M,A>& ma) {
  ContT<R,M,B> r;
  r.unContT = arr(std::function<M<R>(F<B,M<R>>)>([=](F<B,M<R>> k) {
    return mf.unContT(arr(std::function<M<R>(F<A,B>)>([=](F<A,B> f) {
      return ma.unContT(arr(std::function<M<R>(A)>([=](A a) {
        return call(k, call(f, a));
      })));
    })));
  }));
  return r;
}

#endif // __CONTT_HPP__
