#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd1(13, A0, 10, 9, 8, 7);

const int encoder= 6;

const int hole=20;
const int pi =3.14;
const int wheel_radius = 3; //in cm
float dist;

float Distance(int var){
  float cir=2*pi*wheel_radius; //in cm
  dist=dist+(RPS(var)*cir*var)/1000;
  
  
  Serial.print(var);
  Serial.print(",");
  Serial.println(dist);
  
  
  return dist;
}

float RPS(int var){
  float rps=1000/float(hole*var);
  return rps;
}

float RPM(int var){
  return RPS(var)*60;
}

float Speed(int var){
  float cir=2*pi*wheel_radius; //in cm
  return RPS(var)*cir;
}

void setup() {
  lcd.begin(16, 2);
  lcd1.begin(16, 2);
  Serial.begin(9600);
  
  lcd.print("Distance - ");
  lcd1.print("Speed c/s  - ");
  
  lcd.setCursor(0,1);
  lcd1.setCursor(0,1);
  
  lcd.print("RPM  - ");
  lcd1.print("RPS  - ");

  pinMode(encoder,INPUT);
  
  dist=0;
}

void loop() {
  int temp = digitalRead(encoder);  

  float diff=0;
  if(temp==0){
    int curr_time=millis();
    while(digitalRead(encoder)==0);
    while(digitalRead(encoder)==1);
    diff=millis()-curr_time;
  }
  
  if(diff==0){diff=1;}
  
  //diff=diff/1000;
  //Serial.println(diff);
  
  
  // LCD output
  lcd.setCursor(11, 0);
  lcd1.setCursor(11, 0);

  lcd.print(Distance(diff));lcd.print("    ");
  lcd1.print(Speed(diff));lcd.print("    ");
  lcd.setCursor(8,1);
  lcd1.setCursor(8,1);

  lcd.print(RPM(diff));lcd.print("      ");
  lcd1.print(RPS(diff));lcd.print("      ");
  
}