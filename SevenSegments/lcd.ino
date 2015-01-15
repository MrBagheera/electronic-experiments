#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(63,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// LCD
uint8_t letter_b[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b10001,
  0b11110 
};
uint8_t letter_g[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
uint8_t letter_d[8] = {
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b11111,
  0b10001
};
uint8_t letter_zh[8] = {
  0b10101,
  0b10101,
  0b01110,
  0b01110,
  0b00100,
  0b01110,
  0b10101,
  0b10101
};
uint8_t letter_i[8] = {
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b10001
};
uint8_t letter_l[8] = {
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b10001
};
uint8_t letter_p[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001
};
uint8_t letter_f[8] = {
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b00100
};
uint8_t letter_sh[8] = {
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111
};
uint8_t letter_sha[8] = {
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};
uint8_t letter_tv_z[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110
};
uint8_t letter_mg_z[8] = {
  0b11000,
  0b01000,
  0b01000,
  0b01000,
  0b01110,
  0b01001,
  0b01001,
  0b01110
};
uint8_t letter_e[8] = {
  0b01110,
  0b10001,
  0b00001,
  0b01111,
  0b00001,
  0b00001,
  0b10001,
  0b01110
};
uint8_t letter_ju[8] = {
  0b10010,
  0b10101,
  0b10101,
  0b11101,
  0b10101,
  0b10101,
  0b10101,
  0b10010
};
uint8_t letter_ja[8] = {
  0b01111,
  0b10001,
  0b10001,
  0b01111,
  0b00011,
  0b00101,
  0b01001,
  0b10001
};



void setupLCD() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
 
  lcd.createChar(0, letter_p);
  lcd.createChar(1, letter_i);
  lcd.createChar(2, letter_l);
  lcd.createChar(3, letter_sh);
  lcd.createChar(4, letter_g);
  lcd.createChar(5, letter_d);
  lcd.createChar(6, letter_zh);
  lcd.createChar(7, letter_ja);

  lcd.home();
  lcd.write((int) 0);
  lcd.print("P");
  lcd.write(1);
  lcd.print("ET MAKC");
  lcd.write(1);
  lcd.print("M!");
  lcd.setCursor(0, 1);
  lcd.cursor();
  lcd.blink();  
}
