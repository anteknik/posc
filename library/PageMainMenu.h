#ifndef PAGEMAINMENU_H
#define PAGEMAINMENU_H

#include "Page.h"

class PageMainMenu : public Page {
public:
  void draw(HDC hdc) override;
  void onClick(int x, int y, ATMApp &app) override;
  void onKey(char key, ATMApp &app) override;
};

#endif // PAGEMAINMENU_H
