#include <LiquidCrystal.h>
#include "pitches.h"


// LCD pins <--> Arduino pins
const int rs = 8, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int ledred = 11; //Door Closed Status
int ledgreen = 12; // Door Open Status
int sensor = 6; // Door sensor connected to Pin 6 in Arduino
//two variables to read state of switch either on or off

int transformer = 10;//Shocking module step up transformer 
int switchRead = 7;// Read state of switch (to set Arming or disarming)
int melodyPin,ledblue_buzzer = 13; //LED and buzzer pins (common 5V connection)

int song = 1;//pick song  1,2, or 3 
// Christmas songs Source: https://create.arduino.cc/projecthub/joshi/piezo-christmas-songs-fd1ae9


void setup()
{
// you can now interact with the LCD, e.g.:
  lcd.begin(16, 2);
  //Inputs
  pinMode(sensor, INPUT);
  pinMode(switchRead, INPUT);
  
  //Outputs
  pinMode(ledgreen, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(transformer,OUTPUT);
  pinMode(ledblue_buzzer,OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{ 
  if (digitalRead(sensor) == HIGH)//User keeps door shut
  {
    digitalWrite(ledgreen, LOW);
    digitalWrite(ledred, HIGH);
    lcd.clear();
    lcd.print("Door is closed");        // print message at (0, 0)
    lcd.setCursor(0,1);
    lcd.print("System Unarmed!");
    digitalWrite(transformer, LOW);
    digitalWrite(ledblue_buzzer, LOW); 

    Serial.println("Your Door is Closed");
    
  }
  else //User opens the door
  {
    Serial.println("Your Door is Open");
    
    digitalWrite(ledgreen, HIGH);//Turn on green LED
    digitalWrite(ledred, LOW);//Turn off Red LED
    //LCD Update
    lcd.clear();
    lcd.print("Door is open!");  
    lcd.setCursor(0,1);
    lcd.print("System Unarmed!");
    
    //Tactile Switch check if user opens the door
    if (digitalRead(switchRead) == HIGH)   //If switch is high (user activated switch) turn on xfmr
    {
      Serial.println("XFMR On");
      //Update LCD Display
      lcd.clear();
      lcd.print("Door is open!");  
      lcd.setCursor(0,1);
      lcd.print("System ARMED");
      
      //Activate LED and buzzer
      digitalWrite(ledblue_buzzer, HIGH);//Turns on LED and powers buzzer
      //Buzzer christmas song :)
      //sing(song);
      
      //Turn on transformer module for a couple seconds  
      delay(2000);//Small delay before shock
      digitalWrite(transformer, HIGH);//Initiate shock
      delay(5000);//Shock for 5 seconds
      //digitalWrite(transformer, LOW);//Turn off
    if (digitalRead(switchRead) == LOW)   //If switch is low after shock turn everything off
    {  
      digitalWrite(transformer, LOW);  
      digitalWrite(ledblue_buzzer, LOW);
      Serial.println("Off XFMR");  
    }
    else
    {
      digitalWrite(transformer, LOW);//Turn off xfmr
      digitalWrite(ledblue_buzzer, LOW);
      //LCD Update
      lcd.clear();
      lcd.print("Reset! Wait 30s");  
      for(int count = 30; count > 0; count--)
      {
        Serial.println(count);
        lcd.setCursor(0,1);
        lcd.print(count);
        delay(1000);
      }      
      //delay(30000);//30 seconds to turn off switch 
    }
    }   
     //If switch is low (user switch off) turn off xfmr
    if (digitalRead(switchRead) == LOW)  
    {  
      digitalWrite(transformer, LOW);  
      digitalWrite(ledblue_buzzer, LOW); 
      Serial.println("Off XFMR");  
    }
    
  }
  delay(100);
}
