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

#endif // __MONAD_HPP__
