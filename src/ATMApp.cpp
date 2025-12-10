#include "../library/ATMApp.h"
#include "../library/PageLogin.h"

ATMApp::ATMApp(HINSTANCE hInstance) : hInst(hInstance), hWnd(NULL) {
  const char CLASS_NAME[] = "ATM Application";

  WNDCLASS wc = {};
  wc.lpfnWndProc = ATMApp::WndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 128)); // Dark Blue Background

  RegisterClass(&wc);

  hWnd = CreateWindowEx(0, CLASS_NAME, "ATM BCA Simulation",
                        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800,
                        600, NULL, NULL, hInstance, this);

  // Initial page
  navigateTo(std::make_unique<PageLogin>());
}

int ATMApp::run(int nCmdShow) {
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}

void ATMApp::navigateTo(std::unique_ptr<Page> newPage) {
  currentPage = std::move(newPage);
  repaint();
}

void ATMApp::repaint() { InvalidateRect(hWnd, NULL, TRUE); }

LRESULT CALLBACK ATMApp::WndProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam) {
  ATMApp *pApp = NULL;

  if (message == WM_NCCREATE) {
    CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
    pApp = (ATMApp *)pCreate->lpCreateParams;
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pApp);
    pApp->hWnd = hWnd; // Ensure hWnd is set
  } else {
    pApp = (ATMApp *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
  }

  if (pApp) {
    switch (message) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);

      // Set default text colors
      SetBkMode(hdc, TRANSPARENT);
      SetTextColor(hdc, RGB(255, 255, 255)); // White Text

      if (pApp->currentPage) {
        pApp->currentPage->draw(hdc);
      }
      EndPaint(hWnd, &ps);
    }
      return 0;

    case WM_LBUTTONDOWN:
      if (pApp->currentPage) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        pApp->currentPage->onClick(x, y, *pApp);
      }
      return 0;

    case WM_CHAR:
      if (pApp->currentPage) {
        pApp->currentPage->onKey((char)wParam, *pApp);
      }
      return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    }
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}
