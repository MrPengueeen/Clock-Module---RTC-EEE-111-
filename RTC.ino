// Date and time clock using RTC DS1307 & 16*2 LCD Display

#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"


RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup () {
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
  }
  delay(100);

  lcd.begin(16, 2);
}

void loop () {


  DateTime now = rtc.now();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("TIME:");
  timePrint();

  lcd.setCursor(1, 1);
  datePrint();
  delay(1000); //Print date and time every second
}

void timePrint() {
  DateTime now = rtc.now();
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());

}

void datePrint() {
  DateTime now = rtc.now();
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(", ");
  lcd.print(now.day());
  lcd.print(".");
  lcd.print(now.month());
  lcd.print(".");
  lcd.print(now.year()); 
} 
