// Sweep
// by BARRAGAN <http://barraganstudio.com>
// This example code is in the public domain.
 
 
#include <Servo.h>
//#include <I2C.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.
 
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
Servo myservo2;
 
int pos = 0;    // variable to store the servo position
int start;
 
void setup()
{
  //myservo.attach(8,605,2441);  // attaches the servo on pin 8 to the servo object
  myservo.attach(8,1500-985, 1500+985); // New Hobbypark vertical servo
  myservo2.attach(9, 1500-830, 1500+830); 
  //I2c.begin();          // Opens & joins the irc bus as master
  //delay(100);        // Waits to make sure everything is powered up before sending or receiving data  
  //I2c.timeOut(50);    // Sets a timeout to ensure no locking up of sketch if I2C communication fails
  Serial.begin(115200);
  myLidarLite.begin();
  start = 1;
}
 
 
void loop()
{
  int i;
  //Serial.println('New Round:');
  int posEven = 0;
  int expand = 2;
  float shrink = 1.0/expand;
  const float pi = 3.1416;
  float dist0, dist1, horAngle0, verAngle0;
  float xTemp, yTemp, zTemp;
  

  //while (Serial.available())
  //{
  //  char ch = Serial.read();
  //  if (ch == 's')
  //  {
  //    start = 1;
  //    Serial.print("I received: ");
  //    Serial.println(ch);
  //    delay(10);
  //  }
  //}

  if (start == 1)
  {
    for(pos = 60*expand; pos <=120*expand; pos += 1)  // goes from 0 degrees to 180 degrees  (115 is the highest it can go)
    {
      //Serial.print("i = ");
      //Serial.println(i);
      //myservo.write(pos);              // tell servo to go to position in variable 'pos'      
  
      myservo.writeFloat(pos*shrink);              // tell servo to go to position in variable 'pos'  
      //delay(20); // used to be 50
  
      for(i = 10*expand; i <= 175*expand; i += 1)
      {                                  // in steps of 1 degree
        //myservo2.write(i); 
        myservo2.writeFloat(i*shrink); 
        if (i == 10*expand)
        {
          delay(1000); 
        }
        else
        {
          delay(10); // used to be 50
        }
  
        //Serial.print(myLidarLite.distance());
        //Serial.print(",");
        //Serial.print(i*shrink);
        //Serial.print(",");
        //Serial.println(pos*shrink);
  
        dist0 = myLidarLite.distance()+3.7; // Add 3.7cm for distance between laser sensor and rotation center
        dist1 = 1.9;
        horAngle0 = -i*shrink;
        verAngle0 = -pos*shrink+95;  // newly refined result is 91.8 degree
        if (dist0 >= 10)  // dist = 1 when it can't find anything; 4000 is the range for the scanner
        {
          xTemp = -(dist0*cos(verAngle0/180.0*pi) + dist1) * sin(-horAngle0/180.0*pi);
          yTemp = (dist0*cos(verAngle0/180.0*pi) + dist1) * cos(-horAngle0/180.0*pi);
          zTemp = dist0*sin(verAngle0/180.0*pi);
  
          Serial.print(xTemp);
          Serial.print(" ");
          Serial.print(yTemp);
          Serial.print(" ");
          Serial.println(zTemp);
        }
        else
        {
          Serial.print(0);
          Serial.print(" ");
          Serial.print(0);
          Serial.print(" ");
          Serial.println(0);
        }
        
        
        
        //myLidarLite.distance();
        //GetDist();
                              // waits 15ms for the servo to reach the position
      }              
    }
    Serial.println("-1");
    start = 0;
  }

}

