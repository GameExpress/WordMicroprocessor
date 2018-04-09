//Word Microprocessor
//Version 0.2

//Version 0.2 update notes:
//Added save & load feature

//Version 0.1 update notes:
//App released as demo

#include <Arduboy2.h>
Arduboy2 arduboy;
#include "Keyboard.h"
#include "PopupWindow.h"

bool writing;
uint8_t menu;
bool scrShr;
bool alreadySave;
bool alreadyLoad;

void setup() {
  arduboy.boot();
  arduboy.clear();
  arduboy.setFrameRate(15);
  Serial.begin(9600);
}

void loop() {
  if(!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  if(writing) {
    autoKeyboard();
    if(arduboy.justPressed(A_BUTTON) and getCursor() == 0) writing = false;
  } else {
    arduboy.setCursor(0,0);
    arduboy.print(F("Word Microproccesor\n\nNEW FILE\nOPEN FILE\nLOAD FILE\nSAVE FILE\nSCR SHARE"));
    arduboy.drawRect(0,16 + menu * 8,56,8);
    if(arduboy.justPressed(UP_BUTTON) and menu > 0) menu--;
    else if(arduboy.justPressed(DOWN_BUTTON) and menu < 4) menu++;
    if(arduboy.justPressed(A_BUTTON)) {
      if(windowExists()) {
        switch(menu) {
          case 0:
            deleteDocument();
            removePopupWindow();
            writing = true;
            break;
          case 2:
            if(!alreadyLoad) {
              loadDocument();
              if(loadSucceded()) {
                setTextWindow("Load successful!",0);
                setTextWindow("",1);
              }else{
                setTextWindow("Failed to load!",0);
                setTextWindow("No file exists",1);
              }alreadyLoad = true;
            }else {alreadyLoad = false; removePopupWindow();}
            break;
          case 3:
            if(!alreadySave) {
              saveDocument();
              setTextWindow("Save successful!",0);
              setTextWindow("",1);
              alreadySave = true;
            }else {alreadySave = false; removePopupWindow();}
            break;
        }
      }else{
        createPopupWindow(4,20,120,24);
        switch(menu) {
          case 0:
            setTextWindow("Create new file?",0);
            setTextWindow("You'll delete this",1);
            break;
          case 1:
            writing = true;
            removePopupWindow();
            break;
          case 2:
            setTextWindow("Load file from EEPROM?",0);
            setTextWindow("You'll delete this",1);
            break;
          case 3:
            setTextWindow("Save file to EEPROM?",0);
            setTextWindow("You'll overwrite!",1);
            break;
          case 4:
            scrShr = !scrShr;
            if(scrShr) {
              setTextWindow("Screen share is",0);
              setTextWindow("now enabled!",1);
            }else{
              setTextWindow("Screen share is",0);
              setTextWindow("now disabled!",1);
            }break;
        }
      }
    }if(arduboy.justPressed(B_BUTTON)) {removePopupWindow(); alreadySave = false; alreadyLoad = false;}
  }drawPopupWindow();
  if(scrShr) {
    Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  }arduboy.display(true);
}
