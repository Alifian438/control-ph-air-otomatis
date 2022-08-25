//sensor ph
#define pinPH               A0
#define suhuPengukuran      25
 
#include "DFRobot_PH.h"
 
DFRobot_PH ph;
 
float voltagePH;
float phValue;
float Po = 0; 
long millisBacaSensor;

 

//esp
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);
String data;
char c;


//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


//Ph sensor
//const int ph_Pin  = A0;
//float Po = 0;
//float Pa = 0;
//float PH_step;
//int nilai_analog_PH;
//double TeganganPh;
//
////untuk kalibrasi
//float PH4 = 631;
//float PH7 = 400; 

void setup()
{
  
//  pinMode (ph_Pin, INPUT);
  //Serial.begin(9600);
  lcd.begin();

  //relay
  relay1:pinMode(8, OUTPUT);
  relay2:pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);

  //esp
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(10);

//  Sensor pH
ph.begin();
  
}

void loop() {
//  nilai_analog_PH = analogRead(ph_Pin);
//  Serial.print("Nilai ADC Ph: ");
//  Serial.println(nilai_analog_PH);
//  if(nilai_analog_PH >= 636 && nilai_analog_PH <= 664 ){
//    Po = 5.4;
//    }
//  else if(nilai_analog_PH == 465){
//    Po = 10.0;
//  }else if(nilai_analog_PH == 481){
//    Po = 11.0;
//  } 
//  Serial.print("Nilai PH cairan: ");
//  Serial.println(Po, 2);
//  delay(3000);
//  TeganganPh = 5 / 1024.0 * nilai_analog_PH;
//  Serial.print("TeganganPh: ");
//  Serial.println(TeganganPh, 3);
//
//  PH_step = (PH4 - PH7) * 3;
//  Po = 7.00 + ((PH7 - nilai_analog_PH) / PH_step); 
//  float a = Po +5.00;     
//  Serial.print("Nilai PH cairan: ");
//  Serial.println(Po, 2);
//  delay(3000);

//sensor ph
if (millisBacaSensor < millis())
  {
    millisBacaSensor = millis() + 3000;
 
    voltagePH = analogRead(pinPH) / 1024.0 * 5000;          // read the ph voltage
    phValue    = ph.readPH(voltagePH, suhuPengukuran);      // convert voltage to pH with temperature compensation
    Po = phValue + 7.00;
 
    byte PH = round(phValue);
    
 
    Serial.println();
    Serial.print("voltagePH = ");
    Serial.println(voltagePH);
    Serial.print("phValue = ");
    Serial.println(Po);
    Serial.print("PH = ");
    Serial.println(PH);
  }
 
  if (Serial.available())
  {
    Serial.readString();
 
    Serial.println();
    Serial.println("Proses kalibrasi, ikuti petunjuk di serial monitor");
     
    ph.calibration(voltagePH, suhuPengukuran, "ENTERPH");
 
    while (!Serial.available());
    Serial.readString();
     
    voltagePH = analogRead(pinPH) / 1024.0 * 5000;      // read the ph voltage
    ph.calibration(voltagePH, suhuPengukuran, "CALPH");
 
    ph.calibration(voltagePH, suhuPengukuran, "EXITPH");
  }


  //lcd
  lcd.setCursor(5,0);
  lcd.print("PH AIR");
  lcd.setCursor(5,1);
  lcd.print(Po);

//esp
while(mySerial.available()>0){
    delay(10);
    c = mySerial.read();
    data += c;
  }  
  
  if (data.length()>0) {
    Serial.println(data);
    if (data == "PH UP") {
      digitalWrite(8, LOW);
      delay(3000);
      digitalWrite(8, HIGH);
      Serial.println("PH UP");
    } 
    else if (data == "PH DOWN") {
      digitalWrite(9, LOW);
      delay(3000);
      digitalWrite(9, HIGH);
      Serial.println("RELAY OFF");
    }
    else if (data == "PH UP STOP") {
      digitalWrite(8, HIGH);
      Serial.println("PH UP STOP");
    }
    else if (data == "PH DOWN STOP") {
      digitalWrite(9, HIGH);
      Serial.println("PH DOWN STOP");
    } 
    else if (data == "PH AIR") {
      mySerial.print(Po);
      Serial.println(Po);
    }
    
    
    data = "";
  
  }
  //logika ketika ph kelebihan

    //ketika ph di bawah 6
//    if(Po < 6){
//    digitalWrite(8, LOW);
//    delay(3000);
//    digitalWrite(8, HIGH);
//    }
//
//    //ketika ph lebih dari 7
//    else if (Po > 7){
//    digitalWrite(9, LOW);
//    delay(3000);
//    digitalWrite(9, HIGH);
//  }

  
  
  
  

  
}

/*
 * PH step = (tegangan PH4 – tegangan PH7) / (PH7 - PH4)
             = (3.1 – 2.5)/(7-4)
             = 0.6/3
             = 0.2
 */
