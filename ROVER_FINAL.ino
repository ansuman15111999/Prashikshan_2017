
#include<NewPing.h>
#define Trig 3
#define echo 2
#define Max_distance 200

NewPing sonar(Trig,echo,Max_distance);

float P=0;
float I=0;
float D=0;
float PIDvalue;
int error=0;
int previousError=0;

int mode;

int count=0;

int distance=0;

int start=0;

 byte irSensor0=A0;
 byte irSensor1=12;
 byte irSensor2=8;
 byte irSensor3=7;
 byte irSensor4=5;
 byte irSensor5=4;
 byte irSensor6=A2;
 byte irSensor7=A1;



byte lm1=9;
byte lm2=6;

byte rm1=11;
byte rm2=10;

int sensor[8]={0,0,0,0,0,0,0,0};

int Kp=10;
int Ki=1;
int Kd=2;
int MaxSpeed=90;

int stopa=11;
int backwardBluetooth=5;
int forwardBluetooth=4;
int leftBluetooth=2;
int rightBluetooth=3;


int newCount=0;

void setup() {

  Serial.begin(9600);
 pinMode(irSensor0,INPUT);
 pinMode(irSensor1,INPUT);
 pinMode(irSensor2,INPUT);
 pinMode(irSensor3,INPUT);
 pinMode(irSensor4,INPUT);
 pinMode(irSensor5,INPUT);
 pinMode(irSensor6,INPUT);
 pinMode(irSensor7,INPUT);
 Serial.begin(9600);
   
  
    pinMode(lm1,OUTPUT);
    pinMode(lm2,OUTPUT);

    pinMode(rm1,OUTPUT);
    pinMode(rm2,OUTPUT); 
}

void loop() {

  if(Serial.available()&&start==0){
    int incomingByte=Serial.read();
    if(incomingByte==4)
    start++;
    Serial.write('u');
  }
   if(Serial.available()){
    int incomingByte=Serial.read();
    if(incomingByte==10)
    start--; 
  }
  sensorValue();
//  sensorshow();
  Serial.print("MODE");
  Serial.print(" : ");
  Serial.println(mode);
  normalFollow();
  allBlack();
  leftOrRight();
//  bluetoothControl();
  ultraSonic();

   if(midSensor())Serial.println("true");
   else Serial.println("false");
}

                                                                     void sensorValue(){
sensor[0] = digitalRead(irSensor0);
sensor[1] = digitalRead(irSensor1);
sensor[2] = digitalRead(irSensor2);
sensor[3] = digitalRead(irSensor3);
sensor[4] = digitalRead(irSensor4);
sensor[5] = digitalRead(irSensor5);
sensor[6] = digitalRead(irSensor6);
sensor[7] = digitalRead(irSensor7);

errorCalculation();
}




                                                                          void errorCalculation(){


                                                                            
  
error=(-4*sensor[0])+(-3*sensor[1])+(-2*sensor[2])+(-1*sensor[3])+(1*sensor[4])+(2*sensor[5])+(3*sensor[6])+(4*sensor[7]);
Serial.println(error);

if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0&&sensor[4]==0&&sensor[5]==0&&sensor[6]==0&&sensor[7]==0){
  mode=4;
  newCount=0;
  stopage();
}

else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1&&sensor[5]==1&&sensor[6]==1&&sensor[7]==1){
  mode=5;

}

else if(error<=-9){
mode=1;
newCount=0;
stopage();
}

else if(error>=9){
mode=2;
newCount=0;
stopage();
}

else
{
  mode=3;
  newCount=0;
}
}




                                                                 void sensorshow(){
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print(sensor[2]);
  Serial.print("\t");
  Serial.print(sensor[3]);
  Serial.print("\t");
  Serial.print(sensor[4]);
  Serial.print("\t");
  Serial.print(sensor[5]);
  Serial.print("\t");
  Serial.print(sensor[6]);
  Serial.print("\t");
  Serial.println(sensor[7]);
  Serial.print("\t");
}





void calculatePID()
{
  P = error;
  I = I + error;
  D = error-previousError;
  PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
  if(I<-20)
  {
    I=-20;
  }
  if(I>20)
  {
    I=20;
  }
  previousError = error;
}








                                                                void bluetoothControl(){
  
    if(mode==5&&start==1){
          
      if(newCount==0){
      Serial.println("stopUNDER");
      Serial.println(newCount);
      stopage();
      }
      
      if(Serial.available()>0){
        int reading=Serial.read();
        newCount++;
        Serial.println(newCount);
        
          if(reading==forwardBluetooth){
           forwardBlue();
           Serial.println("forward is herer you can do anytging you wnat ot do");
           }
      
          else if(reading==backwardBluetooth){
          backward();
          Serial.println("backward");
           }
           
          else if(reading==rightBluetooth){
          rightBlue();
          }
          
         else if(reading==leftBluetooth){
         leftBlue();
         }
     
         else if(reading==stopa){
         stopage();
         newCount=0;
        }
    }
    }
}


void leftOrRight(){


  if(mode==1&&start==1){
      stopage();
      Serial.write('R');
      Serial.println("stop");
  if(Serial.available()){
  int comingByte=Serial.read();
  if(comingByte==14){
    Serial.println("right us gerer sfaslfhas;lfhaspofhos");
    
   Serial.write('k'); 
    
    right();
    
  }
   else if(comingByte==forwardBluetooth){
      forwardBlue();
     }
  }
}


if(mode==2&&start==1){
   stopage();
   Serial.write('L');
      Serial.println("stop");
  if(Serial.available()){
  int comingByte=Serial.read();
  if(comingByte==2){
    Serial.println("left is here you can do what you want");
    left();
  }
   else if(comingByte==forwardBluetooth){
      forwardBlue();
     }
  }  
}
}




void allBlack(){
    if(mode==4&&start==1){
      stopage();
      Serial.println("stop");
      
      Serial.write('B');
    
  if(Serial.available()>0){
    
     int comingByte=Serial.read();
     
     if(comingByte==2){
     Serial.println("left mode is on you can do what you wnat");
     left();
     }

     else if(comingByte==14){
     Serial.println("right mode is on you can do what you want");
     right();  
     }
     else if(comingByte==forwardBluetooth){
      forwardBlue();
     }
    
     }
}
}




void startOrStop(){
  if(Serial.available()>0){
//  Serial.println("Start or stop Availbale");
  int incomingByte=Serial.read();

  if(incomingByte==10|| incomingByte==11){
  if(incomingByte==10){
  start=1;
  Serial.print("start");
  }
  else if(incomingByte==11){
  start=0;
  Serial.print("stop");
  }
  }
}
}

void normalFollow(){
  if(mode==3&&start==1){
  
//   sensorshow();
     calculatePID();
     motorPIDcontrol();
}
}

void motorPIDcontrol(){
analogWrite(lm1,MaxSpeed-PIDvalue);
analogWrite(lm2,0);

analogWrite(rm1,MaxSpeed+PIDvalue);
analogWrite(rm2,0);
Serial.write('h');

}

void left(){
forward();
  analogWrite(lm1,0);
  analogWrite(lm2,80);

  analogWrite(rm1,80);
  analogWrite(rm2,0);
  
  delay(600);
  sensorValue();
 
  if(midSensor())
    stopage();

  
  
}
void right(){
forward();

  analogWrite(lm1,80);
  analogWrite(lm2,0);

  analogWrite(rm1,0);
  analogWrite(rm2,80);
  delay(600);
  sensorValue();
  if(midSensor())stopage();
  
}

void stopage(){
  analogWrite(lm1,0);
  analogWrite(lm2,0);

  analogWrite(rm1,0);
  analogWrite(rm2,0);
}

void forward(){
   analogWrite(lm1,100);
  analogWrite(lm2,0);

  analogWrite(rm1,100);
  analogWrite(rm2,0);

  delay(750);
}

void forwardBlue(){
   analogWrite(lm1,100);
  analogWrite(lm2,0);

  analogWrite(rm1,100);
  analogWrite(rm2,0);
  
}
void rightBlue(){


  analogWrite(lm1,80);
  analogWrite(lm2,0);

  analogWrite(rm1,0);
  analogWrite(rm2,80);
   delay(500);
  sensorValue();
  if(midSensor())stopage();
}
void leftBlue(){

  analogWrite(lm1,0);
  analogWrite(lm2,80);

  analogWrite(rm1,80);
  analogWrite(rm2,0);
  delay(500);
  sensorValue();
  if(midSensor())stopage();
}
void backward(){
  
  analogWrite(lm1,0);
  analogWrite(lm2,100);

  analogWrite(rm1,0);
  analogWrite(rm2,100);
}

boolean midSensor(){
  if(sensor[3]==0&&sensor[4]==0)
  return true;
  else if((sensor[3]==0&&sensor[4]==0&&sensor[2]==0)||(sensor[3]==0&&sensor[4]==0&&sensor[5]==0))
  return true;
  else
  return false;
  
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=200;
  }
  return cm;
}

void ultraSonic(){
  distance=readPing();
  if(distance<20){
    stopage();
    delay(3000);
    leftBlue();
  }
}



