//when signal output is high the sensor is being pressed

#include <Servo.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial GPS_SoftSerial(4, 3);

TinyGPSPlus gps;
volatile float minutes, seconds;
volatile int degree, secs, mins;
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int sensor=11; //initialises component to arduino digital pins


void setup() {
        myservo.attach(9);
        pinMode(sensor,INPUT);
        Serial.begin(9600);
        Serial.begin(9600); 
        GPS_SoftSerial.begin(9600); 
}

void loop() {

        int value=digitalRead(sensor);
        if(value == HIGH){
                for (pos = 0; pos <= 180; pos += 1) {
                        myservo.write(pos);              // tell servo to go to position in  variable 'pos'
                                delay(15);                       // waits 15ms for the servo to reach the  position
                }
                for (pos = 180; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
                        myservo.write(pos);              // tell servo to go to position in variable 'pos'
                                delay(15);
                }
                Serial.println("TOUCHED ");
        }
        else
        {

                Serial.println("NOT TOUCHED ");
                delay(100);
        }

         smartDelay(1000);
  unsigned long start;
  double lat_val, lng_val, alt_m_val;
  bool loc_valid, alt_valid;
  lat_val = gps.location.lat(); 
  loc_valid = gps.location.isValid(); 
  lng_val = gps.location.lng();
  alt_m_val = gps.altitude.meters(); 
  alt_valid = gps.altitude.isValid(); 

  if (!loc_valid)
  {
    Serial.print("Latitude : ");
    Serial.println("*****");
    Serial.print("Longitude : ");
    Serial.println("*****");
    delay(4000);
  }
  else
  {
    Serial.println("GPS READING: ");
    DegMinSec(lat_val);
    Serial.print("Latitude : ");
    Serial.println(lat_val);

    DegMinSec(lng_val); 
    Serial.print("Longitude : ");
    Serial.println(lng_val);
    delay(4000);
  }
        
}



static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (GPS_SoftSerial.available()) 
    gps.encode(GPS_SoftSerial.read());
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)
{
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}
