# LightUp
[![Build Status](https://travis-ci.org/TanPitch/ButtonKing.svg?branch=master)](https://travis-ci.org/TanPitch/LightUp)
[![Source Line of Code](https://img.shields.io/badge/Lines%20Of%20Code-308-brightgreen.svg)](https://github.com/TanPitch/LightUp)
![](https://img.shields.io/github/release/Light-Up/editor.md.svg)

Light Up is a simple PWM RGB LED controller.
Inspired by the commercial LED light.

Thanks to [FastLED](https://github.com/FastLED/FastLED) and [u8g2](https://github.com/olikraus/u8g2) library.

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
This program was design for 128x32 screen but it was tested on 128x64 screen.
Change this line to correspond screen.
For more information [u8g2](https://github.com/olikraus/u8g2)

```C
// Start up the screen.
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 22, 21, U8X8_PIN_NONE);
```

 > If there is any problem, [please submit an issue on github](https://help.github.com/en/articles/creating-an-issue)

###### ©2019 TANPITCH
