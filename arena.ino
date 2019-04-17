#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
const uint8_t card_uid[] = { 0xC6, 0xDA, 0x10, 0x1A };
const uint8_t card2_uid[] = { 0xB2, 0x44, 0xEA, 0x35 };
 
void setup() {
lcd.init();
lcd.backlight();
lcd.print(" LET'S PLAY!!! ");
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
}
 
int t1 = 5;
int t2 = 5;
 
void loop() {
 
if(!mfrc522.PICC_IsNewCardPresent())
return;
 
if(!mfrc522.PICC_ReadCardSerial())
return;
 
if((mfrc522.uid.size == sizeof(card2_uid)) &&
(memcmp(&mfrc522.uid.uidByte, &card2_uid,
sizeof(card2_uid)) == 0))
{
t1-=1;
lcd.setCursor(0, 0);
lcd.print("time left: ");
lcd.print(t1);
lcd.print("    ");
lcd.setCursor(0, 1);
lcd.print("                ");
 
if(t1<=0)
{
lcd.setCursor(0, 0);
lcd.print("CONGRATULATIONS!");
lcd.setCursor(0, 1);
lcd.print(" Car 2 win!!! ");
delay(5000);
lcd.setCursor(0, 0);
lcd.print(" LET'S PLAY!!!  ");
lcd.setCursor(0, 1);
lcd.print("                ");
t1 = 5;
t2 = 5;
}
}
else
{
  t1 = 5;
}
 
if ((mfrc522.uid.size == sizeof(card_uid)) &&
(memcmp(&mfrc522.uid.uidByte, &card_uid,
sizeof(card_uid)) == 0))
{
t2-=1;
lcd.setCursor(0, 0);
lcd.print("time left: ");
lcd.print(t2);
lcd.print("    ");
lcd.setCursor(0, 1);
lcd.print("                ");
 
if(t2<=0)
{
  lcd.setCursor(0, 0);
  lcd.print("CONGRATULATIONS!");
  lcd.setCursor(0, 1);
  lcd.print(" Car 1 win!!!" );
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print(" LET'S PLAY!!!  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  t1 = 5;
  t2 = 5;
}
}
else
{
  t2 = 5;
}
delay(1000);
}
