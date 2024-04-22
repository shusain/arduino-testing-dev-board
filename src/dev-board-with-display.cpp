
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <FastLED.h>

ClickEncoder *encoder;
int16_t last, value;


// Variable and pin declarations

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// How many leds in your strip?
#define NUM_LEDS 2

#define DATA_PIN 5
// Define the array of leds
CRGB leds[NUM_LEDS];


// Functions
void timerIsr() {
  encoder->service();
}

// put your setup code here, to run once:
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  Serial.begin(9600);
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  
  Serial.println("Setup started");

  // Encoder setup and timer to trigger encoder checks
  encoder = new ClickEncoder(7, 8, 9);
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
}

void updateLEDs() {
  leds[0] = CRGB::BlueViolet;
  FastLED.show();
  delay(50);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(10);

  leds[1] = CRGB::Green;
  FastLED.show();
  delay(50);
  // Now turn the LED off, then pause
  leds[1] = CRGB::Black;
  FastLED.show();
  delay(10);
}

// put your main code here, to run repeatedly:
void loop() {
  Serial.println("looping");

  updateLEDs();
  value += encoder->getValue();
  
  if (value != last) {
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);

    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0, 0);
    //Display static text
    display.print("Temp = ");
    display.println(value);
    display.display();
  }
}
