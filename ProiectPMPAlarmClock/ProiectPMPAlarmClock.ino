#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>

#define P1 3
#define P2 8
#define P3 7
#define P4 5
#define P5 2

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
RTC_DS1307 rtc;

int buzzer_pasiv = 9;
int meniu = 0;
const int debounce = 35;
int activate = 0;
int stop = 0;

int hour, minute, second, day, month, year;
int alarmHour, alarmMinute;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(P4, INPUT_PULLUP);
  pinMode(P5, INPUT_PULLUP);
  pinMode(buzzer_pasiv, OUTPUT);

  Wire.begin();

  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (true)
      ;
  }
  //seteaza automat RTC-ul la data si ora laptopului, la momentul in care acest cod e compilat
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop() 
{

  if (meniu == 0)
  {
    DisplayDateTime();
  }
  
  if (meniu == 1)
  {
    DisplaySetHour();
  }
  if(meniu == 2)
  {
    DisplaySetMinutes();
  }
  if(meniu == 4)
  {
    CheckAlarm();
  }
  if (meniu == 3)
  {
    StoreAgg();
    meniu = 0;
  }
  delay(50);
}

void DisplayDateTime ()
{
  DateTime now = rtc.now();
  if(digitalRead(P5) == LOW)
  {
   meniu = 4;
   delay(debounce);
  }
  if(digitalRead(P1) == LOW)
  {
   meniu = 1;
   delay(debounce);
  }
  if(digitalRead(P4) == LOW)
  {
   meniu = 2;
   delay(debounce);
  }
  lcd.setCursor(0, 1);
  lcd.print("Ora: ");
  if(now.hour() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.hour());
  //Serial.println(now.hour());
  hour = now.hour();
  //Serial.println(hour);
  lcd.print(":");
  if(now.minute() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute());
  minute = now.minute();
  lcd.print(":");
  if(digitalRead(P5) == LOW)
  {
   meniu = 4;
   delay(debounce);
  }
  if(digitalRead(P1) == LOW)
  {
   meniu = 1;
   delay(debounce);
  }
  if(digitalRead(P4) == LOW)
  {
   meniu = 2;
   delay(debounce);
  }
  if(now.second() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.second());

  lcd.setCursor(0, 0);
  lcd.print("Data: ");
  if(now.day() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.day());
  day = now.day();
  lcd.print(".");
  if(digitalRead(P5) == LOW)
  {
   meniu = 4;
   delay(debounce);
  }
  if(digitalRead(P1) == LOW)
  {
   meniu = 1;
   delay(debounce);
  }
  if(digitalRead(P4) == LOW)
  {
   meniu = 2;
   delay(debounce);
  }
  if(now.month() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.month());
  month = now.month();
  lcd.print(".");
  lcd.print(now.year());
  year = now.year();
if(digitalRead(P5) == LOW)
  {
   meniu = 4;
   delay(debounce);
  }
if(digitalRead(P1)==LOW)
{
   meniu = 1;
   delay(debounce);
}
if(digitalRead(P4) == LOW)
  {
   meniu = 2;
   delay(debounce);
  }
   
  if ((now.minute() == alarmMinute) && (now.hour() == alarmHour) && (now.second() < 10)) 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WAKE UP!");
    for (int i = 0; i < 80; i++) { // make a sound
        digitalWrite(buzzer_pasiv, HIGH); // send high signal to buzzer
        delay(1); // delay 1ms
        digitalWrite(buzzer_pasiv, LOW); // send low signal to buzzer
        delay(1);
    }
    delay(50);
    for (int j = 0; j < 100; j++) { //make another sound
        digitalWrite(buzzer_pasiv, HIGH);
        delay(2); // delay 2ms
        digitalWrite(buzzer_pasiv, LOW);
        delay(2);
    }
    delay(100);
  }
  delay(1000);
}

void DisplaySetHour()
{
  lcd.clear();
  DateTime now = rtc.now();
  
  lcd.setCursor(0, 0);
  lcd.print("Set Hour:");
  lcd.setCursor(0, 1);
  lcd.print(hour);
 
  while(digitalRead(P1)){
  if(digitalRead(P2) == LOW)
  {
    if(hour == 23)
    {
      hour = 0;
    }
    else
    {
      hour = hour+1;
    }
    delay(1000);
  
  }
   if(digitalRead(P3) == LOW)
  {
    if(hour == 0)
    {
      hour = 23;
    }
    else
    {
      hour = hour - 1;
    }
    delay(1000);
  }
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print("Set Hour:");
  lcd.setCursor(0, 1);
  lcd.print(hour);
  lcd.print(" ");
  }
  meniu=3;
  delay(debounce);
}

void DisplaySetMinutes()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0, 1);
  lcd.print(minute);

  while(digitalRead(P4)){
    if(digitalRead(P2) == LOW)
    {
      if (minute == 59)
      {
        minute = 0;
      }
      else
      {
        minute = minute + 1;
      }
      delay(1000);
    }
     if(digitalRead(P3) == LOW)
    {
      if (minute == 0)
      {
        minute = 59;
      }
      else
      {
        minute = minute - 1;
      }
      delay(1000);
    }
  lcd.setCursor(0, 0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0, 1);
  lcd.print(minute);
  lcd.print(" ");
  }
  meniu = 3;
  delay(debounce);
}

void CheckAlarm()
{
  DateTime now = rtc.now();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Alarm:");
  lcd.setCursor(0, 1);
  alarmHour = now.hour();
  if(alarmHour < 10)
  {
    lcd.print("0");
  }
  lcd.print(alarmHour);
  lcd.print(":");
  alarmMinute = now.minute();
  if(alarmMinute < 10)
  {
    lcd.print("0");
  }
  lcd.print(alarmMinute);
  while (digitalRead(P5)) 
  {
    if (digitalRead(P3) == LOW) 
    {
      if (alarmMinute == 59) 
      {
        alarmMinute = 0;
      } 
      else 
      {
        alarmMinute = alarmMinute + 1;
      }
      delay(1000);
    }
    if(digitalRead(P2) == LOW)
    {
      if(alarmHour == 23)
      {
        alarmHour = 0;
      }
      else
      {
        alarmHour = alarmHour + 1;
      }
      delay(1000);
    }
    lcd.setCursor(0, 0);
    lcd.print("Set Alarm:");
    lcd.setCursor(0, 1);
    if(alarmHour < 10)
    {
      lcd.print("0");
    }
    lcd.print(alarmHour);
    lcd.print(":");
    if(alarmMinute < 10)
    {
      lcd.print("0");
    }
    lcd.print(alarmMinute);
    lcd.print(" ");
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ALARM SET");
  //Serial.println(alarmMinute);
  delay(1000);
  meniu = 0;
  delay(debounce);
}

void StoreAgg()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SAVING IN");
  lcd.setCursor(0,1);
  lcd.print("PROGRESS");
  rtc.adjust(DateTime(year, month, day, hour, minute, 0));
  delay(200);
}