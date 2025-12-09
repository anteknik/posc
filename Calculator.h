#pragma once

#include <string>
#include <vector>
#include <windows.h>


// Control IDs
#define IDC_DISPLAY 100
#define IDC_BUTTON_0 200
#define IDC_BUTTON_1 201
#define IDC_BUTTON_2 202
#define IDC_BUTTON_3 203
#define IDC_BUTTON_4 204
#define IDC_BUTTON_5 205
#define IDC_BUTTON_6 206
#define IDC_BUTTON_7 207
#define IDC_BUTTON_8 208
#define IDC_BUTTON_9 209
#define IDC_BUTTON_ADD 210
#define IDC_BUTTON_SUB 211
#define IDC_BUTTON_MUL 212
#define IDC_BUTTON_DIV 213
#define IDC_BUTTON_EQU 214
#define IDC_BUTTON_CLR 215

class Calculator {
public:
  Calculator();
  int Run(HINSTANCE hInstance, int nCmdShow);

private:
  HWND hDisplay;
  double currentValue;
  double lastValue;
  int currentOp; // 0: None, 1: Add, 2: Sub, 3: Mul, 4: Div
  bool newNumber;

  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                     LPARAM lParam);
  LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  void CreateControls(HWND hwnd);
  void AddButton(HWND hwnd, const char *text, int x, int y, int w, int h,
                 int id);
  void UpdateDisplay();
  void OnCommand(int id);
};
