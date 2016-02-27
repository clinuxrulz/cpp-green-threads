#ifndef __IDENTITY_HPP__
#define __IDENTITY_HPP__

template <typename A>
struct Identity {
  A value;
};

template <typename A>
Identity<A> mkIdentity(A a) {
  Identity<A> r;
  r.value = a;
  return r;
}

template <typename A>
A runIdentity(Identity<A> ma) {
  return ma.value;
}

template <typename A>
Identity<A> pure(A a) {
  return mkIdentity(a);
}

template <typename A, typename B>
Identity<B> bind(const Identity<A>& ma, const F<A,Identity<B>>& f) {
  return call(f, runIdentity(ma));
}

#endif // __IDENTITY_HPP__
