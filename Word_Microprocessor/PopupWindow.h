#ifndef popupwindow_h
#define popupwindow_h

struct Window {
  int16_t x;
  int16_t y;
  uint8_t w;
  uint8_t h;
  bool e;
  String txt1;
  String txt2;
};Window win;

void createPopupWindow(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  win.x = x;
  win.y = y;
  win.w = w;
  win.h = h;
  win.e = true;
}

void removePopupWindow() {
  win.e = false;
}

void setTextWindow(String txt, bool n) {
  if(n) win.txt2 = txt;
  else win.txt1 = txt;
}

void drawPopupWindow() {
  if(win.e) {
    arduboy.drawRect(win.x, win.y, win.w, win.h, BLACK);
    arduboy.drawRect(win.x + 1, win.y + 1, win.w - 2, win.h - 2,WHITE);
    arduboy.fillRect(win.x + 2, win.y + 2, win.w - 4, win.h - 4,BLACK);
    arduboy.setCursor(win.x + 2, win.y + 2);
    arduboy.print(win.txt1);
    arduboy.setCursor(win.x + 2, win.y + 10);
    arduboy.print(win.txt2);
  }
}

bool windowExists() {
  return win.e;
}

#endif
