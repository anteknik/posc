#include "Calculator.h"
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  Calculator app;
  return app.Run(hInstance, nCmdShow);
}
