//Light-Up 1.1 ©2019 TANPITCH
#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>
#include <U8g2lib.h>
#include <OneButton.h>

#define LED_PIN 17
#define LED_NUM 12
#define BT_UP_PIN 13
#define BT_DOWN_PIN 5
#define BT_ENTER_PIN 23

byte LED_Mode = 0;
byte LED_Eff = 0; // LED effect types
byte LED_Int = 100; // Brightness 0-100
unsigned int LED_Temp = 2200; // Temperature 1000 - 40000
unsigned int LED_HUE = 0; // Hue 0-359
byte LED_Sat = 100; // Sat 0-100
int Eff_Val = 0;

byte SC_Select = 0;

CRGB leds[LED_NUM];
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 22, 21, U8X8_PIN_NONE);

OneButton EnterBT(BT_ENTER_PIN, true);
OneButton UpBT(BT_UP_PIN, true);
OneButton DownBT(BT_DOWN_PIN, true);

// Color Correction
int Temp_RGB_Red(int T){
  double Red_Value;
  if(T <= 6500){ Red_Value = 255; }
  else{ Red_Value = 150.0326 + (1191.569 - 150.0326)/(1 + pow( (T/1726.246), 1.647998 ) ) ; }
  return Red_Value;
}
int Temp_RGB_Green(int T){
  double Green_Value;
  if(T <= 6600){ Green_Value = 431.7675 + (-1563.118 - 431.7675)/(1 + pow( (T/36.93633), 0.4430906 ) ) ; }
  else if(T >= 6800){ Green_Value = 185.1882 + (1974.011 - 185.1882)/(1 + pow( (T/765.391), 1.532935 ) ) ; }
  else{ Green_Value = 250; }
  return Green_Value;
  //©tanpitch 2019
}
int Temp_RGB_Blue(int T){
  double Blue_Value;
  if(T <= 1990){ Blue_Value = 0; }
  else if(T <= 6500){ Blue_Value = 749.0347 + (-2053137 - 749.0347)/(1 + pow( (T/8.119498e-8), 0.3316271 ) ); }
  else{ Blue_Value = 255; }
  return Blue_Value;
}

static unsigned char Splash_Logo_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x03, 0x00, 0x06, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x03, 0x00,
  0x06, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x06, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x06, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x06, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x07, 0xE6, 0xC0, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x83, 0xCF, 0xF6, 0xE1, 0x87, 0x81,
  0xB1, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xC3, 0xFD,
  0xBE, 0xE3, 0x87, 0x81, 0xF1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x00, 0xE3, 0x30, 0x1E, 0xC7, 0x80, 0x81, 0xF1, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x63, 0x60, 0x0E, 0xC6, 0x80, 0x81,
  0x71, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x63, 0x60,
  0x06, 0xC6, 0x80, 0x81, 0x31, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x63, 0x60, 0x06, 0xC6, 0x80, 0x81, 0x31, 0x60, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x63, 0x60, 0x06, 0xC6, 0x80, 0x81,
  0x31, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x63, 0x60,
  0x06, 0xC6, 0x80, 0x81, 0x31, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x63, 0x60, 0x06, 0xC6, 0x80, 0x81, 0x31, 0x60, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x63, 0x70, 0x06, 0xC6, 0x80, 0x81,
  0x31, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xE3, 0x38,
  0x06, 0xC6, 0x80, 0x81, 0x31, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0x00, 0xC3, 0x1F, 0x06, 0xC6, 0x81, 0x81, 0x31, 0x60, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x83, 0x0F, 0x06, 0x86, 0x81, 0x81,
  0x31, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x03, 0x00,
  0x06, 0x86, 0x83, 0x83, 0x33, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF8, 0x3F, 0x03, 0x0C, 0x06, 0x06, 0x0F, 0xFF, 0xB7, 0x1D, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F, 0x03, 0x1C, 0x06, 0x06, 0x0E, 0xFC,
  0xB6, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
  0x00, 0x00, 0x00, 0x00, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F,
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

void OLED_Status(){
  u8g2.setFont(u8g2_font_siji_t_6x10); //12x12 A7
  u8g2.drawGlyph(106, 18, 57855); // Battery 53,54,55, 56 - Charging
  //© T A N P I T C H 2 0 1 9
}

void OLED_Splash(){
  u8g2.clearBuffer();
  u8g2.drawXBM( 0, 0, 128, 32, Splash_Logo_bits);
  u8g2.setFont(u8g2_font_profont17_mr); //9x17 A11
  u8g2.drawStr( 90, 25, "1.0");
  u8g2.sendBuffer();
}

void OLED_Main(byte selector){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont17_mr); //9x17 A11
  switch(selector){
    case 0: u8g2.drawStr( 39, 21, "CCT"); break; // CCT
    case 1: u8g2.drawStr( 39, 21, "HSL"); break; // HSL
  }
  u8g2.setFont(u8g2_font_profont12_mr); //6x11 A8
  switch(selector){
    case 0: u8g2.drawStr( 10, 20, "HSL"); u8g2.drawStr( 72, 20, "HSL"); break; // CCT
    case 1: u8g2.drawStr( 10, 20, "CCT"); u8g2.drawStr( 72, 20, "CCT"); break; // HSL
    //©2019 TANPITCH
  }
  OLED_Status();
  u8g2.sendBuffer();
}

void OLED_CCT(byte selector){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont17_mr); //9x17 A11
  u8g2.setCursor(  5, 21); u8g2.print(LED_Temp); u8g2.drawStr( 41, 21, "K");
  if(LED_Int == 100){ u8g2.setCursor( 59, 21); } else if(LED_Int <= 9){ u8g2.setCursor( 77, 21); } else{ u8g2.setCursor( 68, 21); } u8g2.print(LED_Int);  u8g2.drawStr( 86, 21, "%");
  if(selector == 0){ u8g2.drawBox( 3, 8, 49, 15); } else if(selector == 1){ u8g2.drawBox( 57, 8, 40, 15); }
  OLED_Status(); //©TANPITCH 2019
  u8g2.sendBuffer();
}

void OLED_HSL(byte selector){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont17_mf); //9x17 A11
  switch(selector){ // Space 82
    case 0: // HUE
      u8g2.drawStr( 14, 21, "HUE");
      if(LED_HUE >= 100){ u8g2.setCursor( 50, 21); } else if(LED_HUE >= 10){ u8g2.setCursor( 59, 21); } else{ u8g2.setCursor( 68, 21); } u8g2.print(LED_HUE); u8g2.setCursor( 77, 21); u8g2.print("\xb0");
      u8g2.drawBox( 48, 8, 40, 15);
    break;

    case 1: // SAT
      u8g2.drawStr( 14, 21, "SAT");
      if(LED_Sat >= 100){ u8g2.setCursor( 50, 21); } else if(LED_Sat >= 10){ u8g2.setCursor( 59, 21); } else{ u8g2.setCursor( 68, 21); } u8g2.print(LED_Sat);
      u8g2.setCursor( 77, 21); u8g2.print("%");
      u8g2.drawBox( 48, 8, 40, 15);
    break;

    case 2: // INT
      u8g2.drawStr( 14, 21, "INT");
      if(LED_Int >= 100){ u8g2.setCursor( 50, 21); } else if(LED_Int >= 10){ u8g2.setCursor( 59, 21); } else{ u8g2.setCursor( 68, 21); } u8g2.print(LED_Int);
      u8g2.setCursor( 77, 21); u8g2.print("%");
      u8g2.drawBox( 48, 8, 40, 15); //©2019 TANPITCH
    break;

  }
  u8g2.setFont(u8g2_font_siji_t_6x10); //7x7
  u8g2.drawGlyph(0, 19, 57678); u8g2.drawGlyph(93, 19, 57679); // Left Right Arrows
  OLED_Status();
  u8g2.sendBuffer();
}

void EnterClick(){
  switch(LED_Mode){
    case 1: LED_Mode = SC_Select + 2; SC_Select = 0; break; //Main Screen
    case 2: if(SC_Select == 1){ SC_Select = 0; } else{ SC_Select = 1; } break; //CCT
    case 3: if(SC_Select != 2){ SC_Select++; } else{ SC_Select = 0; } break; //HSL
  }
}

void EnterPress(){ SC_Select = LED_Mode - 2; LED_Mode = 1; }

void UpClick(){
  switch(LED_Mode){
    case 1: if( SC_Select != 0 ){ SC_Select--; } else{ SC_Select = 2; } break; // Main Screen
    case 2: // CCT Mode
      switch(SC_Select){
        case 0: if( LED_Temp <= 9980){ LED_Temp+=10; } break; // Tempurature
        case 1: if( LED_Int <= 99){ LED_Int++; } break;        // Intensity ©2019 TANPITCH
      }
    break;
    case 3: // HSL Mode
      switch(SC_Select){
        case 0: if( LED_HUE <= 358){ LED_HUE++; } else{ LED_HUE = 0; } break; // HUE
        case 1: if( LED_Sat <= 99){ LED_Sat++; } break;                       // Saturation
        case 2: if( LED_Int <= 99){ LED_Int++; } break;                       //Intensity
      }
    break;
  }
}

void UpPress(){
  EVERY_N_MILLIS(50){
    switch(LED_Mode){
      case 2: // CCT Mode
        switch(SC_Select){
          case 0: if( LED_Temp <= 9980){ LED_Temp+=10; } break; // Tempurature
          case 1: if( LED_Int <= 99){ LED_Int++; } break;        // Intensity
        }
      break;
      case 3: // HSL Mode
        switch(SC_Select){
          case 0: if( LED_HUE <= 358){ LED_HUE++; } else{ LED_HUE = 0; } break; // HUE
          case 1: if( LED_Sat <= 99){ LED_Sat++; } break;                       // Saturation
          case 2: if( LED_Int <= 99){ LED_Int++; } break;                       //Intensity
        }
      break;
    }
  }
}

void DownClick(){
  switch(LED_Mode){
    case 1: if( SC_Select != 2 ){ SC_Select++; } else{ SC_Select = 0; } break; // Main Screen
    case 2: // CCT Mode
      switch(SC_Select){
        case 0: if( LED_Temp >= 1010){ LED_Temp-=10; } break; // Tempurature
        case 1: if( LED_Int >= 1){ LED_Int--; } break;        // Intensity
      }
    break;
    case 3: // HSL Mode
      switch(SC_Select){
        case 0: if( LED_HUE >= 1){ LED_HUE--; } else{ LED_HUE = 359; } break; // HUE
        case 1: if( LED_Sat >= 1){ LED_Sat--; } break;                       // Saturation
        case 2: if( LED_Int >= 1){ LED_Int--; } break;                       //Intensity
      }
    break;
  }
}

void DownPress(){
  EVERY_N_MILLIS(50){
    switch(LED_Mode){
      case 2: // CCT Mode
        switch(SC_Select){
          case 0: if( LED_Temp >= 1010){ LED_Temp-=10; } break; // Tempurature
          case 1: if( LED_Int >= 1){ LED_Int--; } break;        // Intensity
        }
      break;
      case 3: // HSL Mode
        switch(SC_Select){
          case 0: if( LED_HUE >= 1){ LED_HUE--; } else{ LED_HUE = 359; } break; // HUE
          case 1: if( LED_Sat >= 1){ LED_Sat--; } break;                       // Saturation
          case 2: if( LED_Int >= 1){ LED_Int--; } break;                       //Intensity
        }
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_NUM).setCorrection( TypicalSMD5050 );
  u8g2.begin(); u8g2.setFontMode(1); u8g2.setDrawColor(2);
  EnterBT.setPressTicks(600);
  EnterBT.attachClick(EnterClick);
  EnterBT.attachLongPressStart(EnterPress);
  UpBT.setPressTicks(600);
  UpBT.attachClick(UpClick);
  UpBT.attachDuringLongPress(UpPress);
  DownBT.setPressTicks(600);
  DownBT.attachClick(DownClick);
  DownBT.attachDuringLongPress(DownPress);
  //©2019 TANPITCH
}

void loop() {
  EnterBT.tick(); UpBT.tick(); DownBT.tick();
  switch(LED_Mode){

    case 0: //Splash
      OLED_Splash();
      EVERY_N_MILLIS(50){
        Eff_Val+=5;
        for(byte i=0; i<=LED_NUM-1; i++){ leds[i] = CRGB::White; }
        FastLED.setBrightness( Eff_Val*51/20 );
        FastLED.show();
        if(Eff_Val >= 100){ Eff_Val = 0; LED_Mode = 2; } }
    break;

    case 1: //Main Screen
      OLED_Main(SC_Select);
    break;

    case 2: //CCT Mode
      for(byte i=0; i<=LED_NUM-1; i++){ leds[i] = CRGB( Temp_RGB_Red(LED_Temp), Temp_RGB_Green(LED_Temp), Temp_RGB_Blue(LED_Temp) ); }
      FastLED.setBrightness( LED_Int*51/20 );
      FastLED.show();
      OLED_CCT(SC_Select);
    break;

    case 3: //HSL Mode
      OLED_HSL(SC_Select);
      for(byte i=0; i<=LED_NUM-1; i++){ leds[i] = CHSV( map(LED_HUE, 0, 359, 0, 255), LED_Sat*51/20, LED_Int*51/20); }
      FastLED.show();
    break;
  }


}
