#include "ATM.h"
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  ATM app;
  return app.Run(hInstance, nCmdShow);
}
