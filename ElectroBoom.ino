#include <IRremote.h>
#include <IRremoteInt.h>

#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;         // Pin Assignments for LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int Sensor = 2;                                                       // Magnetic Door Sensor Input
int Transformer = 3;                                                  // Output to Voltage Booster Module
int Remote = 4;                                                       // Remote Input to Arm or Disarm Device
int Buzzer = A1;                                                      // Output to Buzzer

IRrecv irrecv(Remote);                                                // Take input from IR Receiver
decode_results results;                                               // Convert Received Value to HEX

int LEDBlue = 5;                                                      // Armed System LED (Door Open)
int LEDGreen = 6;                                                     // Unarmed System Status (Door Open or Closed)
int LEDRed = 7;                                                       // Armed System Status (Door Closed)

boolean SystemArmed = false;                                          // Flag for System Status
boolean Button = false;                                               // Flag for IR Receiver Status

void setup() 
{
  lcd.begin(16, 2);
  //Inputs
  pinMode(Sensor, INPUT);
  pinMode(Remote, INPUT);

  //Outputs
  pinMode(Transformer, OUTPUT);
  pinMode(LEDBlue, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Transformer, LOW);
  digitalWrite(LEDBlue, LOW);
  digitalWrite(LEDGreen, LOW);
  digitalWrite(LEDRed, LOW);
  irrecv.enableIRIn();                                                // Start the Receiver
  Serial.begin(9600);                                                 // Start the Serial Monitor
}

void loop()
{
  if ((digitalRead(Sensor) == HIGH) && (SystemArmed == true))         //Status Check for Door being Closed and Armed
  {
    Serial.println("System Armed");
    Serial.println("Door Closed");
    analogWrite(LEDRed, 255);
    analogWrite(LEDGreen, 0);
    analogWrite(LEDBlue, 0);
    digitalWrite (Transformer, LOW);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.write("Door Closed!");
    lcd.setCursor(2, 1);
    lcd.write("System Armed");
    Button = false;

    while ((digitalRead(Sensor) == HIGH) && (Button == false))
    {
      if (irrecv.decode(&results))
      {
        if (results.value == 0XFF6897)
        { 
          SystemArmed = false;
          Button = true;
        }
          irrecv.resume();
      }
    }
  }
  if ((digitalRead(Sensor) == LOW) && (SystemArmed == true))        //Status Check for Door being Open and Armed
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.write("Shocking");
    lcd.setCursor(3, 1);
    lcd.write("Isn't It??");
    Button = false;

    while ((digitalRead(Sensor) == LOW) && (Button == false))       // Shocking Stage. Door is Opened and System is Armed. Device Waits for Door Sensor Change or Remote Input
    {                                                                 
      if (irrecv.decode(&results)) 
      {
        if (results.value == 0XFF6897) 
        {                            
          SystemArmed = false;
          Button = true;
        }
          irrecv.resume();
      }
      if ((digitalRead(Sensor) == LOW) && (Button == false))
      {
        Serial.println("Shock Stage");
        Serial.println("System Waiting for Sensor or Remote Input");
        analogWrite(LEDRed, 0);
        analogWrite(LEDGreen, 0);
        analogWrite(LEDBlue, 255);
        digitalWrite(Transformer, HIGH);
        digitalWrite(Buzzer, HIGH);
        delay(2000);
        digitalWrite(Transformer, LOW);
        digitalWrite(Buzzer, LOW);
        delay(1000);
      }
    }
  }
  if ((digitalRead(Sensor) == LOW) && (SystemArmed == false))       //Status Check for Door being Open and Unarmed
  {
    Serial.println("System Unarmed");
    Serial.println("Door Open");
    analogWrite(LEDRed, 0);
    analogWrite(LEDGreen, 255);
    analogWrite(LEDBlue, 0);
    digitalWrite (Transformer, LOW);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.write("Door Open!");
    lcd.setCursor(1, 1);
    lcd.write("System Unarmed");
    Button = false;

    while ((digitalRead(Sensor) == LOW) && (Button == false)) 
    {
      if (irrecv.decode(&results)) 
      {
        if (results.value == 0xFF30CF) 
        {  
          SystemArmed = true;
          Button = true;
        }
          irrecv.resume();
      }
    }
  }
  if ((digitalRead(Sensor) == HIGH) && (SystemArmed == false))      //Status Check for Door being Closed and Unarmed
  {
    Serial.println("System Unarmed");
    Serial.println("Door Closed");
    analogWrite(LEDRed, 0);
    analogWrite(LEDGreen, 255);
    analogWrite(LEDBlue, 0);
    digitalWrite (Transformer, LOW);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.write("Door Closed!");
    lcd.setCursor(1, 1);
    lcd.write("System Unarmed");
    Button = false;
    while ((digitalRead(Sensor) == HIGH) && (Button == false)) 
    {
      if (irrecv.decode(&results)) 
      {
        if (results.value == 0xFF30CF) 
        {  
          SystemArmed = true;
          Button = true;
        }
          irrecv.resume();
      }
    }
  }
}
