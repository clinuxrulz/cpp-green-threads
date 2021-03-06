#ifndef __CONTT_HPP__
#define __CONTT_HPP__

#include "F.hpp"

template <typename R, template <typename> class M, typename A>
struct ContT {
  F<F<A,M<R>>,M<R>> unContT;
};

template <typename R, template <typename> class M, typename A>
M<R> runContT(ContT<R,M,A> c, F<A,M<R>> k) {
  return call(c.unContT, k);
}

template <typename R, template <typename> class M, typename A, typename B>
ContT<R,M,A> callCC(F<F<A,ContT<R,M,B>>,ContT<R,M,A>> f) {
  ContT<R,M,A> r;
  r.unContT = arr([=](F<A,M<R>> k) {
    return call(
      call(f, arr([=](A a) {
        ContT<R,M,B> r2;
        r2.unContT = arr([=](F<B,M<R>> unused) {
          return call(k, a);
        });
        return r2;
      })).unContT,
      k
    );
  });
  return r;
}

template <typename R, template <typename> class M, typename A, typename B>
ContT<R,M,B> map(const F<A,B>& f, const ContT<R,M,A>& ma) {
  ContT<R,M,B> r;
  r.unContT = arr([=](F<B,M<R>> k) {
    return call(ma.unContT,arr([=](A a) {
      return call(k, call(f, a));
    }));
  });
  return r;
}

template <typename R, template <typename> class M, typename A, typename B>
ContT<R,M,B> apply(const ContT<R,M,F<A,B>>& mf, const ContT<R,M,A>& ma) {
  ContT<R,M,B> r;
  r.unContT = arr([=](F<B,M<R>> k) {
    return call(mf.unContT,arr([=](F<A,B> f) {
      return call(ma.unContT,arr([=](A a) {
        return call(k, call(f, a));
      }));
    }));
  });
  return r;
}

template <typename R, template <typename> class M, typename A>
ContT<R,M,A> pure(A a) {
  ContT<R,M,A> r;
  r.unContT = arr<F<A,M<R>>,M<R>>([=](F<A,M<R>> k) {
    return call(k, a);
  });
  return r;
}

template <typename R, template <typename> class M, typename A, typename B>
ContT<R,M,B> bind(const ContT<R,M,A>& ma, const F<A,ContT<R,M,B>>& f) {
  ContT<R,M,B> r;
  r.unContT = arr([=](F<B,M<R>> k) {
    return call(ma.unContT,arr([=](A a) {
      return call(call(f, a).unContT, k);
    }));
  });
  return r;
}

#endif // __CONTT_HPP__
