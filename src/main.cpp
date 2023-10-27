#include <SGUI.h>

#include <cmath>

int add(void) {
  float a, b;
  std::cout << "reply 2 numbers: ";
  std::cin >> a >> b;
  std::cout << "result: " << a+b;
  return 0;
}

int sqrt_(void) {
  float a;
  std::cout << "reply 1 numbers: ";
  std::cin >> a;
  std::cout << "result: " << sqrtf(a);
  return 0;
}


int main() {
  SGUI::Console gc{};

  gc.AddFunction(add, "add");
  gc.AddFunction(sqrt_, "sqrt");
  gc.Start();
  return 0;
}