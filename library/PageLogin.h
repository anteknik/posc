#ifndef PAGELOGIN_H
#define PAGELOGIN_H

#include "Page.h"
#include <string>

class PageLogin : public Page {
public:
  void draw(HDC hdc) override;
  void onClick(int x, int y, ATMApp &app) override;
  void onKey(char key, ATMApp &app) override;

private:
  std::string pinBuffer;
};

#endif // PAGELOGIN_H
