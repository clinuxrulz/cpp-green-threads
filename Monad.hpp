#ifndef __MONAD_HPP__
#define __MONAD_HPP__

template <typename Task>
Task do_(Task ma) {
  return ma;
}

template <typename R, template <typename> class M, typename A, typename... Tasks>
R do_(M<A> task, Tasks... tasks) {
  return bind(task, arr<A,R>([=](A a) { return do_(tasks...); }));
}

template <template <typename> class M, typename A>
M<A> return_(A a) {
  return pure(a);
}

template <template <typename> class M, typename A, typename B>
M<B> lift(const F<A,B>& f, const M<A>& ma) {
  return map(f, ma);
}

template <template <typename> class M, typename R, typename Func, typename Task1, typename... Tasks>
M<R> lift(const Func& f, Task1 task1, Tasks... tasks) {
  return apply(map(f, task1), tasks...);
}

template <typename MR, typename Func, typename Task1, typename... Tasks>
MR apply(const Func& f, Task1 task1, Tasks... tasks) {
  return apply(apply(f, task1), tasks...);
}

#endif // __MONAD_HPP__
