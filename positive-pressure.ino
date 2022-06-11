//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
int relay = 4;
int duration = 10000;


#include <LiquidCrystal_I2C.h>
#include <BMP180.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
BMP180 myBMP(BMP180_ULTRAHIGHRES);
bool relayIsTrig = false;
void setup()
{
  pinMode(relay, OUTPUT);
//  pinMode(relay, INPUT);
  Serial.begin(9600);

  while (myBMP.begin() != true)
  {
    Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
    delay(5000);
  }

  Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free

  lcd.init();                      // initialize the lcd
  //  lcd.init();
  // Print a message to the LCD.
  //  lcd.backlight();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Hello, world!");
  //  lcd.setCursor(0, 1);
  //  lcd.print("Ywrobot Arduino!");
}


void loop()
{
  if (myBMP.getPressure() < 103000) {
    lcd.backlight();
    lcd.setCursor(0, 0); lcd.print("P: ");lcd.print(myBMP.getPressure()); lcd.print(" Pa");
    lcd.setCursor(0, 1); lcd.print("Relay OFF   ");
    Serial.println(myBMP.getPressure());
    digitalWrite(relay, HIGH);
  } else if (myBMP.getPressure() > 103000 && myBMP.getPressure() < 111000) {
    lcd.backlight();
    lcd.setCursor(0, 0); lcd.print("P: ");lcd.print(myBMP.getPressure()); lcd.print(" Pa");
//    lcd.setCursor(0, 1); lcd.print("relay OFF   ");
    Serial.println(myBMP.getPressure());
  } else if (myBMP.getPressure() > 120000) {
    lcd.backlight();
    lcd.setCursor(0, 0); lcd.print("P: ");lcd.print(myBMP.getPressure()); lcd.print(" Pa");
    lcd.setCursor(0, 1); lcd.print("Relay ON  ");
    Serial.println(myBMP.getPressure());
    digitalWrite(relay, LOW);
  }


}
