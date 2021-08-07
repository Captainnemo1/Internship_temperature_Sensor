#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensePin = A3;  //This is the Arduino Pin that will read the sensor output
const int motorPin1  = 6;  
const int motorPin2  =7; 
int buzz = 8;
int sensorInput;    
double temp;         

void setup() {
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(buzz, OUTPUT);
 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp_Sensor");
  lcd.setCursor(0,1);
  lcd.print("By Hussain");
  delay(500);
  lcd.clear();
}

void loop() {
  
  sensorInput = analogRead(A3);      
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 
 
  Serial.print("Current Temperature: ");
  Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(12,0);
  
  if (temp<25){
    lcd.print(temp);
    analogWrite(motorPin1, 0);
    digitalWrite(motorPin2, LOW);
    digitalWrite(buzz,LOW);
  }
  if(temp>=25){
    lcd.print(temp);
    analogWrite(motorPin1, 50);
    digitalWrite(motorPin2, LOW);
    digitalWrite(buzz,LOW);
    
  }
  if(temp>=50){
    lcd.print(temp);
    analogWrite(motorPin1, 150);
    digitalWrite(motorPin2, LOW);
    digitalWrite(buzz,LOW);
    
  }
  if(temp>=75){
    digitalWrite(buzz,HIGH);
    analogWrite(motorPin1, 255);
    digitalWrite(motorPin2, LOW);
    if (temp>=75)
    {
      lcd.print(temp);
      lcd.setCursor(0,1);
      lcd.print("OverHeat");
      delay(500);
      lcd.clear();//Stop after 2 secs
      delay(1000);
    }
  }
    
     
    
}
 