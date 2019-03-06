#include "FastLED.h"


int TriggerPin = 7; // Digital 12 -> HC-SR04 Trigger
int EchoPin = 6;    // Digital 13 -> HC-SR04 Echo
int moep = 3;


#define DATA_PIN    10 //streifen
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS]; 


#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

// HC-SR04 Vcc -> 5V, GNG -> GND

void setup() 
{
  Serial.begin(9600);
  pinMode(moep, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  FastLED.setBrightness(BRIGHTNESS);
  
}

void loop(){

  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(TriggerPin, OUTPUT);
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(EchoPin, INPUT);
  duration = pulseIn(EchoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
    if (cm < 15)
    {
      digitalWrite(moep, HIGH);
      fill_solid(leds, NUM_LEDS,CRGB::Red); 
      FastLED.show();
      delay(cm);
      digitalWrite(moep, LOW);
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      delay(cm*4);
    }
    else if (cm < 25){
      digitalWrite(moep, LOW);
      fill_solid(leds, NUM_LEDS,CRGB::Orange); 
      FastLED.show();
      delay(40);
    }

  else {
   digitalWrite(moep, LOW);
    fill_rainbow( leds, NUM_LEDS, 0, 7);
    FastLED.show();
    delay(40);
  }
  Serial.print(cm);
    Serial.println("cm");
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

