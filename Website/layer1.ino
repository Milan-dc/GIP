#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo myservo;
Servo selector;

const int redPos = 0;
const int bluePos = 45;
const int greenPos = 90;
const int yellowPos = 135;
const int orangePos = 150;
const int brownPos = 180;

int selectorPosition[3] = {14, 100, 180};

void setup() {
  Serial.begin(9600);
  if (!tcs.begin()) {
    Serial.println("Error initializing the color sensor");
    while (1);
  }
  myservo.attach(10);
  selector.attach(9);
  selector.write(0);
  delay(200);
}

void loop() {
  moveSelector(0, 1);
  delay(500);
  
  float red, green, blue;
  tcs.setInterrupt(false); // turn on LED
  delay(60); // takes 50ms to read
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true); // turn off LED
  
  Serial.print("Red: "); Serial.print(int(red));
  Serial.print("  Green: "); Serial.print(int(green));
  Serial.print("  Blue: "); Serial.print(int(blue));

  if (red > 51 && red < 59 && green > 77 && green < 84 && blue > 127 && blue < 136) {
    // Color is red
    myservo.write(redPos);
    Serial.println("  Color: Red");
  } else if (red > 39 && red < 46 && green > 96 && green < 104 && blue > 117 && blue < 124) {
    // Color is green
    myservo.write(greenPos);
    Serial.println("  Color: Green");
  } else if (red > 26 && red < 34 && green > 80 && green < 87 && blue > 150 && blue < 157) {
    // Color is blue
    myservo.write(bluePos);
    Serial.println("  Color: Blue");
  } else if (red > 54 && red < 60 && green > 93 && green < 99 && blue > 102 && blue < 110) {
    // Color is yellow
    myservo.write(yellowPos);
    Serial.println("  Color: Yellow");
  } else if (red > 39 && red < 47 && green > 82 && green < 89 && blue > 137 && blue < 144) {
    // Color is brown
    myservo.write(brownPos);
    Serial.println("  Color: Brown");
  } else if (red > 58 && red < 68 && green > 78 && green < 87 && blue > 111 && blue < 119) {
    // Color is orange
    myservo.write(orangePos);
    Serial.println("  Color: Orange");
  } else {
    // Unknown color
    Serial.println("  Unknown color");
  }
  
  delay(1000);
  moveSelector(1, 2);
  delay(500);
}

void moveSelector(int pos, int target) {
  if (pos < target) {
    for (int i = selectorPosition[pos]; i <= selectorPosition[target]; i++) {
      selector.write(i);
      delay(15);
    }
  }
}
