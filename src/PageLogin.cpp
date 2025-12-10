#include "../library/PageLogin.h"
#include "../library/ATMApp.h"
#include "../library/PageMainMenu.h"

void PageLogin::draw(HDC hdc) {
  // Fonts
  HFONT hFontLarge =
      CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                 DEFAULT_PITCH | FF_SWISS, "Arial");
  HFONT hFontNormal =
      CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                 DEFAULT_PITCH | FF_SWISS, "Arial");

  // Title
  HFONT hOldFont = (HFONT)SelectObject(hdc, hFontLarge);
  const char *title = "WELCOME TO ATM BCA";
  TextOut(hdc, 200, 100, title, strlen(title));

  // Instruction
  SelectObject(hdc, hFontNormal);
  const char *instr = "Please Enter Your PIN (Type on Keyboard):";
  TextOut(hdc, 200, 250, instr, strlen(instr));

  // PIN Masked
  std::string maskedPin(pinBuffer.length(), '*');
  TextOut(hdc, 200, 300, maskedPin.c_str(), maskedPin.length());

  DeleteObject(hFontLarge);
  DeleteObject(hFontNormal);
  SelectObject(hdc, hOldFont);
}

void PageLogin::onClick(int x, int y, ATMApp &app) {
  // Optional: On screen keyboard click check
}

void PageLogin::onKey(char key, ATMApp &app) {
  if (key == VK_RETURN) { // Enter
    Beep(1000, 200);      // Sound effect
    if (pinBuffer == "12345") {
      app.navigateTo(std::make_unique<PageMainMenu>());
    } else {
      pinBuffer.clear();
      Beep(300, 300); // Error sound
      MessageBox(NULL, "Invalid PIN!", "Error", MB_ICONERROR);
      app.repaint();
    }
  } else if (key == VK_BACK) {
    if (!pinBuffer.empty()) {
      pinBuffer.pop_back();
      app.repaint();
    }
  } else if (isdigit(key)) {
    if (pinBuffer.length() < 6) {
      pinBuffer += key;
      Beep(750, 50); // Key click sound
      app.repaint();
    }
  }
}
