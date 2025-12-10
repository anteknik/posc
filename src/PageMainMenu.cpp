#include "../library/PageMainMenu.h"
#include "../library/ATMApp.h"

// Helper for button hit testing
bool isInside(int x, int y, int rectX, int rectY, int width, int height) {
  return x >= rectX && x <= rectX + width && y >= rectY && y <= rectY + height;
}

void PageMainMenu::draw(HDC hdc) {
  HFONT hFont =
      CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                 DEFAULT_PITCH | FF_SWISS, "Arial");
  HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

  TextOut(hdc, 50, 50, "MAIN MENU - Click Option", 24);

  // Set styling for "Standard ATM" look
  SetBkMode(hdc, TRANSPARENT);
  SetTextColor(hdc, RGB(255, 255, 255)); // White Text

  // Create a Pen for button borders (White)
  HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
  HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
  HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // Transparent fill
  HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNullBrush);

  // 1. Check Balance
  Rectangle(hdc, 50, 150, 350, 250);
  TextOut(hdc, 70, 190, "1. -> CEK SALDO", 15);

  // 2. Withdraw
  Rectangle(hdc, 400, 150, 700, 250);
  TextOut(hdc, 420, 190, "2. -> TARIK TUNAI", 17);

  // 3. Exit
  Rectangle(hdc, 50, 300, 350, 400);
  TextOut(hdc, 70, 340, "3. -> KELUAR", 12);

  // Cleanup
  SelectObject(hdc, hOldPen);
  SelectObject(hdc, hOldBrush);
  DeleteObject(hPen);

  DeleteObject(hFont);
  SelectObject(hdc, hOldFont);
}

void PageMainMenu::onClick(int x, int y, ATMApp &app) {
  Beep(800, 100); // Click Sound

  // Check Balance (50, 150, 350, 250)
  if (isInside(x, y, 50, 150, 300, 100)) {
    MessageBox(NULL, "Your Balance is Rp 100.000.000", "Info", MB_OK);
  }
  // Withdraw (400, 150, 700, 250)
  else if (isInside(x, y, 400, 150, 300, 100)) {
    MessageBox(NULL, "Feature Coming Soon", "Info", MB_OK);
  }
  // Exit (50, 300, 350, 400)
  else if (isInside(x, y, 50, 300, 300, 100)) {
    PostQuitMessage(0);
  }
}

void PageMainMenu::onKey(char key, ATMApp &app) {
  // Optional Keyboard shortcuts
}
