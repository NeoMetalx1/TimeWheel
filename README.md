## Simple time wheel

### Usage:

```
#include "timewheel.h"

void func() {
  std::cout << "Hello\n";
}

int main() {
  int wheelsize = 8;
  TimeWheel wheel(wheelsize);

  wheel.start();

          // delay func name
  wheel.addTask(5, func);
  return 0;
}
```
