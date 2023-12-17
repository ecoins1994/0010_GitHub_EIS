//=================================================================================================
//                              1.Setting  Arduino IDE
//=================================================================================================
http://arduino.esp8266.com/stable/package_esp8266com_index.json 
https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json 
https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json
//=================================================================================================
//                                    2.For ESP32
//=================================================================================================
To use additional controllers and/or with controllers with additional properties recommended to replace:
board.txt from CORE ESP32  to 
RT_00_HW_BASE_xx\src\BASE_000_Reference\0120_С++_board.txt\0104_ESP32_borad.txt\board.txt 
//==================================================================================================
//                               3.Supported controllers:
//==================================================================================================
AVR: Arduino UNO,Nano,Pro,MEGA2560;
SAM: Arduino DUE;
ESP8266: ESP8266 GENERIC,LOLIN(WEMOS)D1 mini Lite,LOLIN(WEMOS)D1 mini Pro,NODEMCU 0.9,NODEMCU 1.0;
ESP32S:  ESP32 DEV Module, ESP32S DEV BlueTooth EIS, TTGO T-Display;
ESP32S2: ESP32S2 DEV(в работе);
         LOLIN S2 Mini, LOLIN S2 Pro;
ESP32S3: ESP32S3 DEV(debug);
         BPI-PicoW(debug);
ESP32C3: ESP32C3 DEV,ESP32C3 STAMP-C3 EIS, ESP32C3 STAMP-C3U EIS,ESP32C3_TTGO_T_OI_PLUS_EIS,
         ESP32C3 LuatOS USB EIS, ESP32C3 LuatOS Classic EIS;
ESP32-M5:M5Stack-Core-ESP32, M5Stack-ATOM;
ESP32_Pico: STAMP-PICO;
STM32F1(Clark): Generic STM32F103C series,Generic STM32F103R series,Generic STM32F103V series;
STM32F4(Clark): Generic_STM32F407V, BlackPill F401CCU6, BlackPill F411CE;
STM32F1duino: BluePill F103C8, BluePill F103CB, BlackPill F103C8,BlackPill F103CB,Generic F103CBTx,
              Generic F103RETx,Generic F103VETx;
STM32F4duino: Black F407VE,Black F407VG,Generic F407VETx,Generic F407VGTx,BlackPill F401CC, BlackPill F411CE;
STM32H743Vx;STM32H750Vx;    
SEEEDUINO: Seeeduno XIAO M0, Seeeduno Zero;
RASPBERRY PI PICO: Raspberry Pi Pico, Raspberry Pi Pico W, Raspberry Pi Pico Zero(from IDE name Adafruit KB2040);
-----------------------------------------------------------------------------------------------------    
