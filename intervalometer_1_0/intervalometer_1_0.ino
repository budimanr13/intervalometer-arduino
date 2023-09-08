//OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 5
Adafruit_SSD1306 display(OLED_RESET);

const int pin_A = 4;                      // rotary switch CLK
const int pin_B = 3;                      // rotary switch DT
const int Rotbutton = 2;                   // rotary switch SW (push button) 
const int Switch = 6;                      // toggle switch to start
const int Trigger = 7;                     // trigger PIN

float Interval = 3;                        // Interval on start
float Incremvalue = 1.0;                   // how many +/- to the interval
unsigned long currentTime;
unsigned long loopTime;
unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev = 0;


void setup()  {
  Serial.begin(9600);

  //OLED Display
  Wire.begin();
  Wire.setClock(400000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  pinMode(Trigger, OUTPUT);
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  pinMode(Rotbutton, INPUT);
  pinMode(Switch, INPUT);

  currentTime = millis();
  loopTime = currentTime;
  
  digitalWrite(Trigger, LOW);


}

void loop()  {

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(" Interval:  ");
 

  if (digitalRead(Switch) == LOW) {

    // get the current elapsed time
    currentTime = millis();
    if (currentTime >= (loopTime + 5)) {
      // 5ms since last check of encoder = 200Hz
      encoder_A = digitalRead(pin_A);    // Read encoder pins
      encoder_B = digitalRead(pin_B);
      if ((!encoder_A) && (encoder_A_prev)) {
        // A has gone from high to low
        if (encoder_B) {
          // B is high so clockwise
          // increase the Interval, dont go over 255
          if (Interval + Incremvalue <= 255) Interval += Incremvalue;
        }
        else {
          // B is low so counter-clockwise
          // decrease the Interval, dont go below 0
          if (Interval - Incremvalue >= 0) Interval -= Incremvalue;
        }
        
          display.print(Interval);
          display.print(" s");
          display.display();
        
      }
      encoder_A_prev = encoder_A;     // Store value of A for next time

      

      loopTime = currentTime;  // Updates loopTime

     if (digitalRead(Rotbutton) == LOW) {
         digitalWrite(Trigger, HIGH);
         digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)  
         delay(200);
         digitalWrite(Trigger, LOW);
         digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW  
         delay(200);
     }
    
    Serial.println(Interval);
    }

    


  } else {
    digitalWrite(Trigger, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)  
    delay(200);
    digitalWrite(Trigger, LOW);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW  
    delay(1000 * Interval);
  }




}
