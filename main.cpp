#include <iostream>
#include "F.hpp"
#include "ContT.hpp"
#include "Identity.hpp"
#include "Monad.hpp"

void testContT() {
  ContT<int,Identity,int> x = pure<int,Identity,int>(1);
  std::cout << runIdentity(runContT(x, arr<int,Identity<int>>([=](int x) {
    return mkIdentity(x);
  }))) << std::endl;
}

void testDoNotation() {
  Identity<int> ma = return_<Identity>(42);
  Identity<int> mb = do_<Identity<int>>(
    ma,
    ma
  );
  std::cout << runIdentity(mb) << std::endl;
}

void testLift() {
  Identity<int> ma = return_<Identity>(40);
  Identity<int> mb = return_<Identity>(2);
  Identity<int> mc = lift<Identity,int>(
    arr<int,F<int,int>>([=](int x) {
      return arr<int,int>([=](int y) {
        return x + y;
      });
    }),
    ma,
    mb
  );
  std::cout << runIdentity(mc) << std::endl;
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
  testDoNotation();
  testLift();
  return 0;
}