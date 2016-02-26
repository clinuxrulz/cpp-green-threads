#ifndef __F_HPP__
#define __F_HPP__

#include <memory>
#include <functional>

enum SuspenderType {
  SUSPEND,
  DONE
};

template <typename A>
struct Suspender
{
  SuspenderType type;
  std::function<Suspender<A>()> resume;
  A done;
};

template <typename A>
A runSuspender(Suspender<A> a) {
  while (a.type != DONE) {
    a = a.resume();
  }
  return a.done;
}

template <typename A>
Suspender<A> done(A a) {
  Suspender<A> r;
  r.type = DONE;
  r.done = a;
  return r;
}

template <typename A>
Suspender<A> suspend(std::function<Suspender<A>()> resume) {
  Suspender<A> r;
  r.type = SUSPEND;
  r.resume = resume;
  return r;
}

template <typename A, typename B>
struct F
{
  std::function<Suspender<B>(A)> func;
};

template <typename A, typename B, class Func>
F<A,B> arr(Func f) {
  F<A,B> r;
  r.func = [=](A x) { return done(f(x)); };
  return r;
}

template <typename A, typename B>
B call(F<A,B> f, A a) {
  return runSuspender(f.func(a));
}

#endif /* __F_HPP__ */
