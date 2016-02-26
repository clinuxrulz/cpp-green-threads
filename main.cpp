#include <iostream>
#include "F.hpp"
#include "ContT.hpp"
#include "Identity.hpp"

void testContT() {
  ContT<int,Identity,int> x = pure<int,Identity,int>(1);
  std::cout << runIdentity(runContT(x, arr<int,Identity<int>>([=](int x) {
    return mkIdentity(x);
  }))) << std::endl;
}

int main(int argc, char** argv) {
  Suspender<int> x = done(2);
  Suspender<int> y =
    suspend(std::function<Suspender<int>()>([=]() {
      return suspend(std::function<Suspender<int>()>([=]() { return x; }));
    }));
  F<int,int> f = arr<int,int>([](int a) { return a + 1; });
  std::cout << runSuspender(y) << std::endl;
  std::cout << call(f, 5) << std::endl;
  testContT();
  return 0;
}