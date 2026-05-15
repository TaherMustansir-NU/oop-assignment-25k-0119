#include "src/App.h"
#include <exception>
#include <iostream>

using namespace std;

int main() {
  try {
    App app;
    app.run();
  } catch (exception &e) {
    cout << "Error: " << e.what() << endl;
    return 1;
  }

  return 0;
}