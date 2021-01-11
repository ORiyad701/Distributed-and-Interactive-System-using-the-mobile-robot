#include <Wire.h>
 
 long dura, dis;
// Define trig and echo pins of the ultrasonic sensor
const int trig = 6;
const int echo = 7;

//Define Motor pins
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
 
// Variable for incoming data from the Esp32(Master0
int id;

//Variable to store the data required to be sent from the Arduino to the Esp32
int c=1;

 
 
void setup() {

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Initialize I2C communications as Slave
  Wire.begin(0x04);
   
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  // Function to run when data is sent to master
  Wire.onRequest(requestEvent);
  
  // Setup Serial Monitor 
  Serial.begin(9600);
  Serial.println("I2c communication begins");
}
 
 
void receiveEvent() {
  // read incoming data from the master
  id = Wire.read();
  // Print value of incoming data
  Serial.println(id);
    
}

 void requestEvent() {
  Wire.write(c); // Send the value of variable c to the master
}
void loop() {
   delay(50);

digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);  
  dura = pulseIn(echo, HIGH);
  dis = dura*(0.034/2);
  if(dis<15)
    {
     Serial.println("Distance:");
     Serial.println(dis);
      c=0;}

      else if(dis>15)
      {
        c=1;
      }


          
 if (id==0) {
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);}


   
 else if (id==1){
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 }


 else if (id==2) {
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);}

 else if (id==3) {
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 delay(100);
  c=3;
  
 }

 else if (id==4) {
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
  delay(100);
    c=3;
 }

 else if (id==5){
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);

 delay (500);

 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);

 delay (500); 

 c=2;
 
  
 }
}
