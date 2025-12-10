#include "../library/ATMApp.h"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  ATMApp app(hInstance);
  return app.run(nCmdShow);
}
