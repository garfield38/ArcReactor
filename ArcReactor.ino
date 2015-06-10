//Iron man arc reactor using NeoPixels and Attiny 85
//Created by Jonathan Bush
//Last Updated: 2/10/2015
                       // pixel 0 is middle, 1 is at 11 oclock, 2 thru 10 counter clockwise
#include <Adafruit_NeoPixel.h>
#define N_LEDS 25      // need to define which pin the neopixel data line is connected to
#define DATA_PIN 3     // Data out to NeoPixels
#define BTN_PIN 4      // Button input
#define BTN_DELAY 2000  // To help reduce button bounce
#define NUM_PATTERNS 7 // Define total number of patterns
#define BRIGHTNESS 90  // Max brightness for most patterns, keep lower to reduce current consumption
#define LOWHEART 40    // Low brightness setting of heartbeat pattern
#define HIGHHEART 150  // High brightness setting of heartbeat pattern

uint8_t pattern=1;
uint8_t buttonState=0;
unsigned long mark;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup(){ 
  digitalWrite(BTN_PIN, HIGH);      
  pinMode(BTN_PIN, INPUT);      
  strip.begin(); 
  strip.show(); // Initialize all pixels to 'off' 
}

void loop(){
  //chkBtn(digitalRead(BTN_PIN));  //check to see if button is pressed every loop
  chkBtn(true);  //check to see if button is pressed every loop
  
  if(pattern > NUM_PATTERNS){pattern = 1;}  //If pattern exceeds total pattern options, reset to 1
  //pattern = 3;
  pickPattern(pattern);  //move to pattern selection

}

void pickPattern(uint8_t var){
  switch (var){
    case 1:
    // steady on
    steadylights();
    break;
    
    case 2:
    //propellar type spin
    propspin();
    break;
    
    case 3:
    //glowing
    glow();
    break;
    
    case 4:
    //cheesy smiley face
    smile();
    break;
    
    case 5:
    //bump bump in red
    heartbeat();
    break;
    
    case 6:
    //single spinning
    spinwheel();
    break;
    
    case 7:
    //idle to save battery power
    idle();
    break;
    
  }
}

boolean chkBtn(int buttonState) { 
  if (buttonState == HIGH && (millis() - mark) > BTN_DELAY) { //check to see if button has been pressed and that it is longer than delay to get rid of bouncing.
    //j = 0; 
    mark = millis(); 
    pattern++;
    return true; 
  }  
  else { return false; } 
} 

void steadylights(){
  strip.setBrightness(BRIGHTNESS);
  colorWipe(strip.Color(255,255,255),50); //turn all white
  delay(20);//to keep from blowing through sketch so quickly
}  
  
void spinwheel(){
  strip.setBrightness(BRIGHTNESS);
  for(int i=10;i > 0;i--){
    if(chkBtn(digitalRead(BTN_PIN))){break;}
    strip.setPixelColor(i,255,255,255);
    strip.show();
    delay(100);
    colorWipe(strip.Color(0,0,0),0);
  }
}

void idle(){
  strip.setBrightness(0);
  colorWipe(strip.Color(0,0,0),0);
  delay(50);
}

void propspin(){
  strip.setBrightness(BRIGHTNESS);
  colorWipe(strip.Color(0,0,0),0);
  delay(10);
  for(int j=10; j > 0;j--){
    if(chkBtn(digitalRead(BTN_PIN))){break;}
    int k=j+5;
    if(k>10){k=k-10;}
    strip.setPixelColor(j,255,255,255);
    strip.setPixelColor(k,255,255,255);
    strip.show();
    delay(200);
    colorWipe(strip.Color(0,0,0),0);

  }
}

void glow(){
  colorWipe(strip.Color(255,255,255),10);
  //delay(10);
  for(int m = 1; m < BRIGHTNESS; m++){
    if(chkBtn(digitalRead(BTN_PIN))){break;}
    strip.setBrightness(m);
    strip.show();
    //colorWipe(strip.Color(255,255,255),0);
    //if(m == BRIGHTNESS){x = -1;}
    delay(30);
  }
  for(int m = BRIGHTNESS; m > 0; m--){
    if(chkBtn(digitalRead(BTN_PIN))){break;}
    strip.setBrightness(m);
    strip.show();
    //colorWipe(strip.Color(255,255,255),0);
    //if(m == BRIGHTNESS){x = -1;}
    delay(30);
  }
}

void smile(){
  strip.setBrightness(BRIGHTNESS);
  colorWipe(strip.Color(0,0,0),0);
  strip.setPixelColor(9,255,255,0);
  strip.setPixelColor(1,255,255,0);
  strip.setPixelColor(3,255,255,0);
  strip.setPixelColor(4,255,255,0);
  strip.setPixelColor(5,255,255,0);
  strip.setPixelColor(6,255,255,0);
  strip.setPixelColor(7,255,255,0);
  strip.show();
  delay(20);  //to keep it from processing through the loop so quickly.
}

void heartbeat(){
  strip.setBrightness(LOWHEART);
  colorWipe(strip.Color(255,0,0),0);
  for(int q = 0; q < 76; q++){
    if(chkBtn(digitalRead(BTN_PIN))){break;}
    delay(20);
  }
  strip.setBrightness(HIGHHEART);
  strip.show();
  delay(100);
  strip.setBrightness(LOWHEART);
  strip.show();
  delay(70);
  strip.setBrightness(HIGHHEART);
  strip.show();
  delay(100);
} 

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if(chkBtn(digitalRead(BTN_PIN))){break;}
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
