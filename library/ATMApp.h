#ifndef ATMAPP_H
#define ATMAPP_H

#include "Page.h"
#include <memory>
#include <windows.h>


class ATMApp {
public:
  ATMApp(HINSTANCE hInstance);
  int run(int nCmdShow);

  void navigateTo(std::unique_ptr<Page> newPage);
  void repaint();

private:
  std::unique_ptr<Page> currentPage;
  HWND hWnd;
  HINSTANCE hInst;
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

  // Helper to safely access instance from static WndProc
  void handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif // ATMAPP_H
