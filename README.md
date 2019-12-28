# LightUp
<img alt="Travis (.com)" src="https://img.shields.io/travis/com/TanPitch/Light-Up?style=for-the-badge"> <img src="https://img.shields.io/badge/Lines%20Of%20Code-308-brightgreen?style=for-the-badge"> <img src="https://img.shields.io/badge/RELEASE-v1.1-brightgreen?style=for-the-badge">

Light Up is a simple PWM RGB LED controller.
Inspired by the commercial LED light.

Thanks to [FastLED](https://github.com/FastLED/FastLED) and [u8g2](https://github.com/olikraus/u8g2) library.

### lastest version
<img src="https://img.shields.io/github/v/release/TanPitch/Light-Up?style=for-the-badge"> <img alt="Travis (.org) branch" src="https://img.shields.io/travis/TanPitch/Light-Up/Beta?style=for-the-badge">

LightUp 1.2 beta ([download here](https://github.com/TanPitch/Light-Up/tree/Beta))
* add new light effect mode.
* add battery level indicator.
* add bluetooth connection node.
> not fully function with some minor bugs.

### lastest worked version
LightUp 1.1 ([download here](https://github.com/TanPitch/Light-Up/releases/tag/1.1))
* CCT and HSL mode fully work.
* bugs fix and minor improvement.
* all worked : test on
  * Arduino Zero, Leonardo, Uno, Mega, Due
  * ESP8266 and ESP32
  * STM32 based boards

please read the [install-note](###install-note) before installed.

### check lists

- [x] Color temperature mode with ws2812b color correction.
- [x] RGB mode with custom HUE, Saturature, Intensity.
- [ ] Light effect.
- [ ] Web or app to control the light.
- [ ] Battery level.

### install-note
- This program was design for 128x32 screen but it was tested on 128x64 screen.
Change this line to correspond screen.
For more information [u8g2](https://github.com/olikraus/u8g2)

```C++
// Start up the screen.
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 22, 21, U8X8_PIN_NONE);
```
- The controlling buttons were connected to pin 13, 5 (up and down), 23 (enter) by using INTERNAL PULLUP resistor.
- LED data pin was connected to pin 17, you can change the code to any pin you want.
```C++
#define LED_PIN 17      // LED Data Pin
#define LED_NUM 12      // Total LEDs
#define BT_UP_PIN 13    // Up Button Pin
#define BT_DOWN_PIN 5   // Down Button Pin
#define BT_ENTER_PIN 23 // Enter Button Pin
```

 > If there is any problem, [please submit an issue on github](https://help.github.com/en/articles/creating-an-issue)
