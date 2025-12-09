#include "ATM.h"

#define ATM_BLUE RGB(0, 51, 153)
#define ATM_TEXT RGB(255, 255, 255)

ATM::ATM()
    : hDisplay(NULL), hBlueBrush(NULL), currentState(STATE_LOGIN),
      currentPin("") {}

int ATM::Run(HINSTANCE hInstance, int nCmdShow) {
  const char CLASS_NAME[] = "ATMWindowClass";

  hBlueBrush = CreateSolidBrush(ATM_BLUE);

  WNDCLASS wc = {};
  wc.lpfnWndProc = ATM::WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hbrBackground = hBlueBrush;

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(
      0, CLASS_NAME, "BCA ATM Simulator",
      WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, CW_USEDEFAULT,
      CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, this);

  if (hwnd == NULL)
    return 0;

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  DeleteObject(hBlueBrush);
  return 0;
}

LRESULT CALLBACK ATM::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam) {
  ATM *pATM = NULL;

  if (uMsg == WM_NCCREATE) {
    CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
    pATM = (ATM *)pCreate->lpCreateParams;
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pATM);
  } else {
    pATM = (ATM *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
  }

  if (pATM) {
    return pATM->HandleMessage(hwnd, uMsg, wParam, lParam);
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT ATM::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE:
    ShowLoginScreen(hwnd);
    return 0;

  case WM_CTLCOLORSTATIC: {
    HDC hdcStatic = (HDC)wParam;
    SetTextColor(hdcStatic, ATM_TEXT);
    SetBkColor(hdcStatic, ATM_BLUE);
    return (INT_PTR)hBlueBrush;
  }

  case WM_KEYDOWN: {
    int key = (int)wParam;
    if (currentState == STATE_LOGIN) {
      if (key >= '0' && key <= '9')
        OnCommand(hwnd, IDC_BUTTON_0 + (key - '0'));
      else if (key >= VK_NUMPAD0 && key <= VK_NUMPAD9)
        OnCommand(hwnd, IDC_BUTTON_0 + (key - VK_NUMPAD0));
      else if (key == VK_RETURN)
        OnCommand(hwnd, IDC_BUTTON_ENTER);
      else if (key == VK_BACK)
        OnCommand(hwnd, IDC_BUTTON_CLEAR);
      else if (key == VK_ESCAPE)
        OnCommand(hwnd, IDC_BUTTON_CLEAR);
    }
  }
    return 0;

  case WM_COMMAND:
    OnCommand(hwnd, LOWORD(wParam));
    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
}

void ATM::ClearScreen(HWND hwnd) {
  HWND child = GetWindow(hwnd, GW_CHILD);
  while (child) {
    HWND next = GetWindow(child, GW_HWNDNEXT);
    DestroyWindow(child);
    child = next;
  }
}

void ATM::AddLabel(HWND hwnd, const char *text, int x, int y, int w, int h,
                   int fontSize, bool center) {
  DWORD style = WS_VISIBLE | WS_CHILD;
  style |= (center ? SS_CENTER : SS_RIGHT);

  HWND hLabel =
      CreateWindow("STATIC", text, style, x, y, w, h, hwnd, NULL, NULL, NULL);

  HFONT hFont =
      CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                 DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                 DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
  SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void ATM::AddButton(HWND hwnd, const char *text, int x, int y, int w, int h,
                    int id) {
  CreateWindow("BUTTON", text,
               WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_FLAT,
               x, y, w, h, hwnd, (HMENU)((UINT_PTR)id),
               (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void ATM::ShowLoginScreen(HWND hwnd) {
  ClearScreen(hwnd);
  currentState = STATE_LOGIN;
  currentPin = "";

  AddLabel(hwnd, "MASUKKAN PIN\nATM ANDA", 450, 50, 300, 60, 28);
  // Removed "BENAR" label
  AddLabel(
      hwnd,
      "DEMI KEAMANAN\nDAN KENYAMANAN\nSILAKAN\nGANTI PIN ANDA\nSECARA BERKALA",
      450, 300, 300, 140, 20);
  AddLabel(hwnd, "TEKAN CANCEL UNTUK PEMBATALAN", 100, 500, 600, 30, 20, true);

  hDisplay = CreateWindow(
      "STATIC", "",
      WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, 150, 130,
      200, 40, hwnd, (HMENU)IDC_DISPLAY, NULL, NULL);
  HFONT hFontPin =
      CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                 DEFAULT_PITCH | FF_SWISS, "Arial");
  SendMessage(hDisplay, WM_SETFONT, (WPARAM)hFontPin, TRUE);

  int startX = 150;
  int startY = 200;
  int w = 60;
  int h = 50;
  int gap = 10;

  AddButton(hwnd, "1", startX, startY, w, h, IDC_BUTTON_1);
  AddButton(hwnd, "2", startX + w + gap, startY, w, h, IDC_BUTTON_2);
  AddButton(hwnd, "3", startX + (w + gap) * 2, startY, w, h, IDC_BUTTON_3);

  startY += h + gap;
  AddButton(hwnd, "4", startX, startY, w, h, IDC_BUTTON_4);
  AddButton(hwnd, "5", startX + w + gap, startY, w, h, IDC_BUTTON_5);
  AddButton(hwnd, "6", startX + (w + gap) * 2, startY, w, h, IDC_BUTTON_6);

  startY += h + gap;
  AddButton(hwnd, "7", startX, startY, w, h, IDC_BUTTON_7);
  AddButton(hwnd, "8", startX + w + gap, startY, w, h, IDC_BUTTON_8);
  AddButton(hwnd, "9", startX + (w + gap) * 2, startY, w, h, IDC_BUTTON_9);

  startY += h + gap;
  AddButton(hwnd, "0", startX + w + gap, startY, w, h, IDC_BUTTON_0);

  // Removed ">" button
  AddButton(hwnd, "CANCEL", startX + (w + gap) * 3 + 20, 200, 80, 50,
            IDC_BUTTON_CLEAR);
  AddButton(hwnd, "ENTER", startX + (w + gap) * 3 + 20, 260, 80, 50,
            IDC_BUTTON_ENTER);
}

void ATM::ShowMenuScreen(HWND hwnd) {
  ClearScreen(hwnd);
  currentState = STATE_MENU;

  AddLabel(hwnd, "SILAKAN MEMILIH TRANSAKSI", 100, 50, 600, 50, 32, true);
  AddLabel(hwnd, "UNTUK PEMBATALAN TEKAN CANCEL", 100, 100, 600, 30, 20, true);

  int btnW = 250, btnH = 50, startY = 200, gap = 40;
  AddButton(hwnd, "TARIK TUNAI", 50, startY, btnW, btnH, IDC_BTN_MENU_1);
  AddButton(hwnd, "INFORMASI SALDO", 50, startY + btnH + gap, btnW, btnH,
            IDC_BTN_MENU_2);

  AddButton(hwnd, "TRANSFER", 500, startY, btnW, btnH, IDC_BTN_MENU_3);
  AddButton(hwnd, "PEMBAYARAN", 500, startY + btnH + gap, btnW, btnH,
            IDC_BTN_MENU_4);

  AddButton(hwnd, "EXIT", 500, startY + (btnH + gap) * 3, btnW, btnH,
            IDC_BUTTON_CLEAR);
}

void ATM::UpdateDisplay() {
  std::string masked = "";
  for (size_t i = 0; i < currentPin.length(); i++)
    masked += "*";
  SetWindowText(hDisplay, masked.c_str());
}

void ATM::OnCommand(HWND hwnd, int id) {
  if (currentState == STATE_LOGIN) {
    if (id >= IDC_BUTTON_0 && id <= IDC_BUTTON_9) {
      if (currentPin.length() < 6) {
        currentPin += std::to_string(id - IDC_BUTTON_0);
        UpdateDisplay();
      }
    } else if (id == IDC_BUTTON_CLEAR) {
      // Updated: Cancel closes the application
      PostQuitMessage(0);
    } else if (id == IDC_BUTTON_ENTER) {
      if (currentPin == "12345") {
        ShowMenuScreen(hwnd);
      } else {
        currentPin = "";
        UpdateDisplay();
        MessageBox(hwnd, "PIN SALAH!", "Error", MB_OK | MB_ICONERROR);
      }
    }
  } else if (currentState == STATE_MENU) {
    if (id == IDC_BUTTON_CLEAR) {
      ShowLoginScreen(hwnd);
    } else if (id >= IDC_BTN_MENU_1 && id <= IDC_BTN_MENU_4) {
      MessageBox(hwnd, "Fitur belum tersedia.", "Info",
                 MB_OK | MB_ICONINFORMATION);
    }
  }
}
