#pragma once

#include <string>
#include <vector>
#include <windows.h>


// Control IDs remain mostly valid, will add MENU IDs
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

#define IDC_BUTTON_ENTER 214
#define IDC_BUTTON_CLEAR 215

// Menu Buttons
#define IDC_BTN_MENU_1 301
#define IDC_BTN_MENU_2 302
#define IDC_BTN_MENU_3 303
#define IDC_BTN_MENU_4 304

enum ATMState { STATE_LOGIN, STATE_MENU };

class ATM {
public:
  ATM();
  int Run(HINSTANCE hInstance, int nCmdShow);

private:
  HWND hDisplay;
  HBRUSH hBlueBrush;
  ATMState currentState;
  std::string currentPin;

  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                     LPARAM lParam);
  LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  void ShowLoginScreen(HWND hwnd);
  void ShowMenuScreen(HWND hwnd);
  void ClearScreen(HWND hwnd);

  void AddButton(HWND hwnd, const char *text, int x, int y, int w, int h,
                 int id);
  void AddLabel(HWND hwnd, const char *text, int x, int y, int w, int h,
                int fontSize = 20, bool center = false);

  void UpdateDisplay();
  void OnCommand(HWND hwnd, int id);
};
