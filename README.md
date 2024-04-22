# Gikafun Dev board

Firmware for a dev board with an array of inputs and outputs hooked to an Arduino Pro Micro 16MHz 328p board and a 128x64 I2C LCD at address 0x3C.

The board also has a rotary encoder hooked up to pins 7,8,9 and a spot for doing PWM output on pin 5 (3 pin hook up like servo connector for either string of LEDs or servo connections)# arduino-testing-dev-board

Firmware can be built using PlatformIO plugin in vs-code (will handle getting dependencies from platformio.ini file and setup the toolchain).  Once cloned open vs-code then use platformIO to open the cloned folder as a project and then use the check and arrow buttons in the status panel of vs-code to compile/upload.