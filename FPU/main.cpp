#include <iostream>

float add(float a, float b) {
  float result;
  __asm__ __volatile__(
    "flds %1;"
    "flds %2;"
    "fadd;"
    "fstps %0;" : "=g" (result) : "g" (a), "g" (b)
  );

  return result;
}

float sub(float a, float b) {
  float result;
  __asm__ __volatile__(
    "flds %2;"
    "flds %1;"
    "fsub;"
    "fstps %0;" : "=g" (result) : "g" (a), "g" (b)
  );

  return result;
}

float mul(float a, float b) {
  float result;
  __asm__ __volatile__(
    "flds %1;"
    "flds %2;"
    "fmul;"
    "fstps %0;" : "=g" (result) : "g" (a), "g" (b)
  );

  return result;
}

float div(float a, float b) {
  float result;
  __asm__ __volatile__(
    "flds %2;"
    "flds %1;"
    "fdiv;"
    "fstps %0;" : "=g" (result) : "g" (a), "g" (b)
  );

  return result;
}

float sqrt(float val) {
  float result;
  __asm__ __volatile__(
    "flds %1;"
    "fsqrt;"
    "fstps %0;" : "=g" (result) : "g" (val)
  );

  return result;
}

int main() {

  std::cout << "Input: a, b, c!" << std::endl;

  float a, b, c;
  std::cin >> a >> b >> c;

  if(!a) {
    std::cout << "Is not a quadratic equation!" << std::endl;
  } else {

    float D = sub(mul(b, b), mul(4, mul(a, c)));

    if(D < 0) {
      std::cout << "D < 0, no roots!" << std::endl;
    } 

    if(D == 0) {
      float root = div(-b, mul(2, a));
      std::cout << "D = 0, root = [" << root << "]!" << std::endl;
    }

    if(D > 0) {
      std::pair<float, float> roots {
        div(sub(-b, -sqrt(D)), mul(2, a)), 
        div(sub(-b,  sqrt(D)), mul(2, a))
      };
      std::cout << "D > 0, roots = [" 
                << roots.first << ", " 
                << roots.second << "]!" << std::endl;
    }

  }

  return 0;
}