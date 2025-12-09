#include "Calculator.h"

Calculator::Calculator()
    : hDisplay(NULL), currentValue(0.0), lastValue(0.0), currentOp(0),
      newNumber(true) {}

int Calculator::Run(HINSTANCE hInstance, int nCmdShow) {
  const char CLASS_NAME[] = "CalculatorWindowClass";

  WNDCLASS wc = {};
  wc.lpfnWndProc = Calculator::WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(
      0, CLASS_NAME, "Calculator",
      WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, CW_USEDEFAULT,
      CW_USEDEFAULT, 300, 400, NULL, NULL, hInstance, this);

  if (hwnd == NULL)
    return 0;

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK Calculator::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                        LPARAM lParam) {
  Calculator *pCalc = NULL;

  if (uMsg == WM_NCCREATE) {
    CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
    pCalc = (Calculator *)pCreate->lpCreateParams;
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pCalc);
  } else {
    pCalc = (Calculator *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
  }

  if (pCalc) {
    return pCalc->HandleMessage(hwnd, uMsg, wParam, lParam);
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Calculator::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam,
                                  LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE:
    CreateControls(hwnd);
    return 0;

  case WM_KEYDOWN: {
    int key = (int)wParam;
    if (key >= '0' && key <= '9') {
      OnCommand(IDC_BUTTON_0 + (key - '0'));
    } else if (key >= VK_NUMPAD0 && key <= VK_NUMPAD9) {
      OnCommand(IDC_BUTTON_0 + (key - VK_NUMPAD0));
    } else {
      switch (key) {
      case VK_ADD:
        OnCommand(IDC_BUTTON_ADD);
        break;
      case VK_SUBTRACT:
        OnCommand(IDC_BUTTON_SUB);
        break;
      case VK_MULTIPLY:
        OnCommand(IDC_BUTTON_MUL);
        break;
      case VK_DIVIDE:
        OnCommand(IDC_BUTTON_DIV);
        break;
      case VK_RETURN:
        OnCommand(IDC_BUTTON_EQU);
        break;
      case VK_BACK:
      case VK_ESCAPE:
        OnCommand(IDC_BUTTON_CLR);
        break;
      // Basic support for main keyboard operators
      case VK_OEM_PLUS:
        OnCommand(IDC_BUTTON_ADD);
        break; // Often '=' without shift, treating as + for simplicity or check
               // shift
      case VK_OEM_MINUS:
        OnCommand(IDC_BUTTON_SUB);
        break;
      }
    }
  }
    return 0;

  case WM_COMMAND:
    OnCommand(LOWORD(wParam));
    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
}

void Calculator::CreateControls(HWND hwnd) {
  hDisplay = CreateWindow(
      "STATIC", "0",
      WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE, 10, 10,
      260, 40, hwnd, (HMENU)IDC_DISPLAY, NULL, NULL);

  HFONT hFont =
      CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                 DEFAULT_PITCH | FF_SWISS, "Arial");
  SendMessage(hDisplay, WM_SETFONT, (WPARAM)hFont, TRUE);

  int x = 10, y = 60, w = 60, h = 60, gap = 5;
  // 7 8 9 /
  AddButton(hwnd, "7", x, y, w, h, IDC_BUTTON_7);
  AddButton(hwnd, "8", x + w + gap, y, w, h, IDC_BUTTON_8);
  AddButton(hwnd, "9", x + (w + gap) * 2, y, w, h, IDC_BUTTON_9);
  AddButton(hwnd, "/", x + (w + gap) * 3, y, w, h, IDC_BUTTON_DIV);

  y += h + gap;
  // 4 5 6 *
  AddButton(hwnd, "4", x, y, w, h, IDC_BUTTON_4);
  AddButton(hwnd, "5", x + w + gap, y, w, h, IDC_BUTTON_5);
  AddButton(hwnd, "6", x + (w + gap) * 2, y, w, h, IDC_BUTTON_6);
  AddButton(hwnd, "x", x + (w + gap) * 3, y, w, h, IDC_BUTTON_MUL);

  y += h + gap;
  // 1 2 3 -
  AddButton(hwnd, "1", x, y, w, h, IDC_BUTTON_1);
  AddButton(hwnd, "2", x + w + gap, y, w, h, IDC_BUTTON_2);
  AddButton(hwnd, "3", x + (w + gap) * 2, y, w, h, IDC_BUTTON_3);
  AddButton(hwnd, "-", x + (w + gap) * 3, y, w, h, IDC_BUTTON_SUB);

  y += h + gap;
  // C 0 = +
  AddButton(hwnd, "C", x, y, w, h, IDC_BUTTON_CLR);
  AddButton(hwnd, "0", x + w + gap, y, w, h, IDC_BUTTON_0);
  AddButton(hwnd, "=", x + (w + gap) * 2, y, w, h, IDC_BUTTON_EQU);
  AddButton(hwnd, "+", x + (w + gap) * 3, y, w, h, IDC_BUTTON_ADD);
}

void Calculator::AddButton(HWND hwnd, const char *text, int x, int y, int w,
                           int h, int id) {
  CreateWindow("BUTTON", text,
               WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y, w,
               h, hwnd, (HMENU)((UINT_PTR)id),
               (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void Calculator::UpdateDisplay() {
  std::string s = std::to_string(currentValue);
  s.erase(s.find_last_not_of('0') + 1, std::string::npos);
  if (s.back() == '.')
    s.pop_back();
  SetWindowText(hDisplay, s.c_str());
}

void Calculator::OnCommand(int id) {
  if (id >= IDC_BUTTON_0 && id <= IDC_BUTTON_9) {
    int digit = id - IDC_BUTTON_0;
    if (newNumber) {
      currentValue = (double)digit;
      newNumber = false;
    } else {
      currentValue = currentValue * 10 + digit;
    }
    UpdateDisplay();
  } else if (id == IDC_BUTTON_CLR) {
    currentValue = 0;
    lastValue = 0;
    currentOp = 0;
    newNumber = true;
    UpdateDisplay();
  } else if (id >= IDC_BUTTON_ADD && id <= IDC_BUTTON_DIV) {
    lastValue = currentValue;
    currentOp = id - IDC_BUTTON_ADD + 1;
    newNumber = true;
  } else if (id == IDC_BUTTON_EQU) {
    if (currentOp == 1)
      currentValue = lastValue + currentValue;
    else if (currentOp == 2)
      currentValue = lastValue - currentValue;
    else if (currentOp == 3)
      currentValue = lastValue * currentValue;
    else if (currentOp == 4 && currentValue != 0)
      currentValue = lastValue / currentValue;

    currentOp = 0;
    newNumber = true;
    UpdateDisplay();
  }
}
