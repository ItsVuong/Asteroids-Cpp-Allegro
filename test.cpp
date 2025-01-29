#include <cmath>
#include <cstdio>
#include <iostream>
int main() {
  std::cout << "Hello world!!!\n";
  float a = 7 * sin(30 * 3.14/180);
  float b = 7 * cos(30*3.14/180);
  double c;
  int count = 0;
  c = tan(a / b);
  a += 0.1;
  std::cout << "result: " << tan(c);
}
