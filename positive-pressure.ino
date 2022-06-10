//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
int relay = 4;
int duration = 2000;
#include <LiquidCrystal_I2C.h>
#include <BMP180.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
BMP180 myBMP(BMP180_ULTRAHIGHRES);
void setup()
{
  pinMode(relay, OUTPUT);
  Serial.begin(9600);

  while (myBMP.begin() != true)
  {
    Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
    delay(5000);
  }

  Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free

  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  //  lcd.backlight();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Hello, world!");
  //  lcd.setCursor(0, 1);
  //  lcd.print("Ywrobot Arduino!");
}


void loop()
{
  lcd.backlight();
  //  Serial.print(F("Pressure: ")); Serial.print(myBMP.getPressure());Serial.println(F(" +-100Pa"));
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Pressure: "); lcd.print(myBMP.getPressure());
  lcd.setCursor(0, 1); lcd.print("Relay: OFF");
  if (myBMP.getPressure() < 110000) {
    digitalWrite(relay, LOW);
    Serial.println(myBMP.getPressure());
  } else {
    digitalWrite(relay, HIGH);
    for (int i = 0 ; i < duration; i++) {
      delay(1);
      Serial.println(myBMP.getPressure());
      lcd.setCursor(0, 0); lcd.print("Pressure: "); lcd.print(myBMP.getPressure());
      lcd.setCursor(0, 1); lcd.print("Relay: ON ");
      if (myBMP.getPressure()  < 105000) {
        digitalWrite(relay, LOW);
        break;
      }
    }
  }
}
