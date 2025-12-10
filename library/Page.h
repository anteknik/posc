#ifndef PAGE_H
#define PAGE_H

#include <windows.h>

class ATMApp;

// Abstract Base Class for all Pages
class Page {
public:
  virtual ~Page() = default;

  // Draw the page content using GDI
  virtual void draw(HDC hdc) = 0;

  // Handle mouse click
  virtual void onClick(int x, int y, ATMApp &app) = 0;

  // Handle keyboard input
  virtual void onKey(char key, ATMApp &app) = 0;
};

#endif // PAGE_H
