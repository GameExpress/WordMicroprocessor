#ifndef keyboard_h
#define keyboard_h
#define null 255

char text[255];
bool shift; //Shift Button on?
bool shLck; //Shift Lock
bool arrSpc; //if in the arrow space
uint8_t mode;
uint8_t cur;
uint8_t tCur;
uint8_t cam;
const unsigned char PROGMEM backspace[12] = {
  10,7,0x8, 0x1c, 0x3e, 0x7f, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 
};const unsigned char PROGMEM enter[8] = {
  6,6,0x8, 0x1c, 0x2a, 0x8, 0x8, 0xf, 
};const unsigned char PROGMEM arrows[30] = {
  14,14,0xc0, 0xe0, 0xf0, 0xc0, 0xc4, 0xc6, 0xff, 0xff, 0xc6, 0xc4, 0xc0, 0xf0, 0xe0, 0xc0, 0x00, 0x1, 0x3, 0x00, 0x8, 0x18, 
  0x3f, 0x3f, 0x18, 0x8, 0x00, 0x3, 0x1, 0x00, 
};const unsigned char PROGMEM exitC[7] = {
  5,5,0x11, 0xa, 0x4, 0xa, 0x11, 
};const unsigned char PROGMEM shiftChar[3][7] = {
  {5,7,0x8, 0x34, 0x22, 0x34, 0x8, },  //Shift Off
  {5,7,0x8, 0x3c, 0x3e, 0x3c, 0x8, },  //Shift On (turns off after another key press)
  {5,7,0x48, 0x7c, 0x7e, 0x7c, 0x48, } //Shift Always on (stays on until pressed the shift key again
};const unsigned char PROGMEM modeChar[3][7] = {
  {5,7,0x2, 0x1e, 0x00, 0x1a, 0x16, }, //Mode Letters
  {5,7,0x55, 0x68, 0x32, 0x68, 0x55, },//Mode Numbers and Symbols
  {5,7,0xe, 0x5, 0x2e, 0x50, 0x7c, }   //Mode Other
};const uint8_t characters[6][33] PROGMEM = {
  {113,119,101,114,116,121,117,105,111,112,
   97,115,100,102,103,104,106,107,108,33,
   122,110,99,118,98,110,109,44,46,45}, //lower case chars
  {81,87,69,82,84,89,85,73,79,80,
   65,83,68,70,71,72,74,75,76,63,
   90,78,67,86,66,78,77,59,58,95}, //UPPER CASE chars
  {48,49,50,51,52,53,54,55,56,57,
   34,35,36,37,38,39,40,41,42,43,
   64,2,7,9,11,124,60,62,47,61}, //Numbers & symbols when shift turned off
  {3,4,5,6,241,242,243,248,249,250,
   247,24,25,26,27,96,123,125,94,126,
   246,1,8,10,12,92,91,93,174,175}, //Numbers & symbols when shift turned on
  {178,179,180,181,182,183,184,185,186,187,
   188,189,190,191,192,193,194,195,196,197,
   198,199,200,201,202,203,204,205,206,207}, //Other symbols when shift turned off
  {208,209,210,211,212,213,214,215,216,217,
   218,219,220,221,222,176,177,13,14,19,
   223,224,225,226,227,228,229,230,231,232} //Other symbols when shift turned on
};uint8_t curChar[33] = {
  113,119,101,114,116,121,117,105,111,112,
  97,115,100,102,103,104,106,107,108,33,
  122,120,99,118,98,110,109,44,46,45
};unsigned char charLocs[35] = {
  null,0,1,2,3,4,5,6,7,8,9,null,null,10,11,12,13,14,15,16,17,18,19,null,null,20,21,22,23,24,25,26,27,28,29
};void drawKeyboard() {
  for(uint8_t x; x < 33; x++) {
    arduboy.drawRect(x%11*8,x/11*10+32,9,11,WHITE);
    arduboy.setCursor(10+x%10*8,2+x/10*10+32);
    arduboy.write(curChar[x]);
  }for(uint8_t x; x < 3; x++) {
    arduboy.drawRect(88,x*10+32,17,11,WHITE);
  }arduboy.drawRect(104,32,24,31,WHITE);
  Sprites::drawOverwrite(109,40,arrows,0);
  Sprites::drawOverwrite(92,34,backspace,0);
  Sprites::drawOverwrite(94,44,enter,0);
  Sprites::drawOverwrite(2,35,exitC,0);
  Sprites::drawSelfMasked(2,45,shiftChar[shift + shLck],0);
  Sprites::drawOverwrite(2,54,modeChar[mode],0);
}void drawCursor() {
  if(cur % 12 == 11) arduboy.drawRect(88,cur / 12 * 10+32,17,11,BLACK);
  else if(cur == 36) arduboy.drawRect(105,33,22,29,WHITE);
  else arduboy.drawRect(cur % 12 * 8,cur / 12 * 10+32,9,11,BLACK);
}void drawCursorAt(uint8_t dCur) {
  if(dCur % 12 == 11) arduboy.drawRect(88,dCur / 12 + 42,17,11,BLACK);
  else if(dCur == 36) arduboy.drawRect(105,33,22,29,WHITE);
  else arduboy.drawRect(dCur % 12 + 8,dCur / 12 + 42,9,11,BLACK);
}void drawTCursor() {
  arduboy.drawRect(tCur % 21 * 6, (tCur / 21 - cam) * 8,5,8,!arduboy.everyXFrames(20));
}void drawTCursorAt(uint8_t dCur) {
  arduboy.drawRect(dCur % 21 * 6, (dCur / 21 - cam) * 8,5,8,!arduboy.everyXFrames(20));
}void changeMode() {
  uint8_t curMod = mode * 2 + shift;
  curChar[0] = pgm_read_byte(&characters[curMod][0]);
  for(uint8_t x = 0; x < 33; x++) {
    curChar[x] = pgm_read_byte(&characters[curMod][x]);
  }
}void shiftCamera() {
  if(tCur / 21 - cam == 0 and cam > 0) cam--;
  else if(tCur / 21 - cam == 3) cam++;
}void drawText() { 
  for(uint8_t x; x < 255; x++) {
    arduboy.setCursor(x % 21 * 6, (x / 21 - cam) * 8);
    if((x / 21 - cam) * 8 > 31) break;
    if(x / 21 - cam > -7) arduboy.write(text[x]);
  }
}void autoKeyboard() {
  drawText();
  drawKeyboard();
  drawCursor();
  drawTCursor();
  if(cur < 36) {
    if(arduboy.justPressed(UP_BUTTON) and cur > 11) cur-=12;
    else if(arduboy.justPressed(DOWN_BUTTON) and cur < 23) cur+=12;
    if(arduboy.justPressed(LEFT_BUTTON) and cur % 12 > 0) cur--;
    else if(arduboy.justPressed(RIGHT_BUTTON)){
      if(cur % 12 < 11) cur++;
      else cur = 36;
    }
  }else{
    if(arduboy.justPressed(UP_BUTTON)) tCur-=21;
    else if(arduboy.justPressed(DOWN_BUTTON)) tCur+=21;
    if(arduboy.justPressed(LEFT_BUTTON)) tCur--;
    else if(arduboy.justPressed(RIGHT_BUTTON)) tCur++;
  }
  if(arduboy.justPressed(A_BUTTON)) {
    if(cur == 36) cur--;
    else if(cur == 35) {text[tCur] = 0;tCur++;}
    else if(cur == 11) {text[tCur] = 0;tCur--;}
    else if(cur == 23) {text[tCur] = '\n';tCur++;}
    else if(cur == 12) {
      if(shLck) {shLck = false;shift = false;}
      else if(shift) shLck = true;
      else shift = true;
      changeMode();
    }else if(cur == 24) {
      mode++;
      if(mode > 2) mode = 0;
      changeMode();
    }else if(cur != 0) {
      text[tCur] = curChar[charLocs[cur]];
      tCur++;
      if(shift and !shLck) {shift = false; changeMode();}
    }
  }shiftCamera();
}void deleteDocument() {
  for(uint8_t x; x < 255; x++) {
    text[x] = 0;
  }
}uint8_t getCursor() {
  return cur;
}uint8_t getTCursor() {
  return tCur;
}

//EEPROM Management

#define EEPROM_C1 EEPROM_STORAGE_SPACE_START + 520
#define EEPROM_C2 EEPROM_C1 + 1
#define EEPROM_START EEPROM_C2 + 1

void saveDocument() {
  EEPROM.update(EEPROM_C1, 'W');
  EEPROM.update(EEPROM_C2, 'P');
  for(uint8_t x = 0; x < 255; x++) {
    EEPROM.put(EEPROM_START + x, text[x]);
  }
}

bool loadSuccess;

void loadDocument() {
  char c1 = EEPROM.read(EEPROM_C1);
  char c2 = EEPROM.read(EEPROM_C2);
  if(c1 != 'W' or c2 != 'P') {loadSuccess = false; return;}
  for(uint8_t x = 0; x < 255; x++) {
    text[x] = EEPROM.read(EEPROM_START + x);
  }loadSuccess = true;
}bool loadSucceded() {
  return loadSuccess;
}
#endif
