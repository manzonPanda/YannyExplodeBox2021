// A basic everyday NeoPixel strip test program.
// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    5
#define LED_COUNT 11

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void fadeUsingCosine(){
  int color;
  int periode = 2000;
  unsigned long currentMillis = millis();
  unsigned long timeZero = currentMillis;

  while( true ){
    currentMillis = millis();
    if ( (currentMillis-timeZero) < 5000 ){
      color = 128+127*cos(2*PI/periode*currentMillis);
      Serial.println(currentMillis);
      strip.setPixelColor(10, strip.Color(color, color,0 ));          // sets the value (range from 0 to 255) 
      strip.show();
    }else{
      break;
    }
  }
}

int previousMillis = 0;
int i = 0;
void initialization(unsigned long currentMillis){
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t yellow = strip.Color(255, 255, 0);
  // Serial.println(currentMillis);
 
  if( (currentMillis == 1000) ){ // delay(1000);
  Serial.print("milli 1000!!!:");
  Serial.println(millis());
  strip.setPixelColor(5, white);
  strip.show();
  }
  if(millis() >= 4000){ //delay(4000);
    if( ( currentMillis-previousMillis > 1000) && i<strip.numPixels()){
      previousMillis = currentMillis;
      if( i == strip.numPixels()-1 ){
        strip.setPixelColor(i, yellow);
        strip.show();
        strip.setPixelColor(i-1, strip.Color(0, 0, 0));
        strip.show();
      }else{
        strip.setPixelColor(i, white);
        strip.show();
        strip.setPixelColor(i-1, strip.Color(0, 0, 0));
        strip.show();
      }
      i++;
      Serial.println(i);
    }

    // for(int i=0; i<strip.numPixels(); i++) {  
    //   if( i== strip.numPixels()-1 ){
    //     strip.setPixelColor(i, yellow);
    //     strip.show();
    //     strip.setPixelColor(i-1, strip.Color(0, 0, 0));
    //     strip.show();
    //   }else{
    //     strip.setPixelColor(i, white);
    //     strip.show();
    //     strip.setPixelColor(i-1, strip.Color(0, 0, 0));
    //     strip.show();
    //   }
    //   delay(200);                         
    // }
  }

    // fadeUsingCosine();
}

bool ledState1 = false;             // ledState used to set the LED
unsigned long previousMillis1 = 0;        // will store last time LED was updated
long OnTime1 = 1000;           // milliseconds of on-time
long OffTime1 = 1000; 
int currentVolume = 0;
void setup() {
  Serial.begin(115200);//115200
  mySoftwareSerial.begin(9600);
  pinMode(A0, INPUT);
  Serial.println("Starting..."); 
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
   
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }else{
    strip.setBrightness(5); // Set BRIGHTNESS (max = 255)
    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    Serial.println(F("DFPlayer Mini online."));
    currentVolume = map(analogRead(A0),0,1023,0,27);
    myDFPlayer.volume(currentVolume);
    myDFPlayer.play(1); //play music
  }
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);        
    strip.show();                         
    delay(wait);                           
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void colorFade(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  for(uint16_t i = 0; i < strip.numPixels(); i++) {
      uint8_t curr_r, curr_g, curr_b;
      uint32_t curr_col = strip.getPixelColor(i); // get the current colour
      curr_b = curr_col & 0xFF; 
      curr_g = (curr_col >> 8) & 0xFF; 
      curr_r = (curr_col >> 16) & 0xFF;  // separate into RGB components
      // Serial.println(curr_col);
      while ( (curr_r != r) || (curr_g != g) || (curr_b != b) ){  // while the curr color is not yet the target color
        if (curr_r < r) 
          curr_r++; 
        else if (curr_r > r)
          curr_r--;  // increment or decrement the old color values
       
        if (curr_g < g) curr_g++; else if (curr_g > g) curr_g--;
        if (curr_b < b) curr_b++; else if (curr_b > b) curr_b--;
        strip.setPixelColor(i, curr_r, curr_g, curr_b);  // set the color
        strip.show();
        delay(wait);  // add a delay if its too fast
      }
      // delay(500);
  }
}

void fadeInOut(){
  int R = 43;
  int G = 43;
  int B = 43;
  //Fade in
  for(R && G && B; R<200 && G<200 && B<200; R++ && G++ && B++) {
    for(int i=0; i<10; i++) {
      strip.setPixelColor(i, strip.Color(R, G, B));
      strip.show();
    }
  }
    // delay(1000);
  //Fade Out
  for(R && G && B; R>43 && G>43 && B>43; R-- && G-- && B--) {
    for(int j=0; j<10; j++) {
      strip.setPixelColor(j, strip.Color(R, G, B));
      strip.show();
    }
  }
}


class MyWs2812{

int index;
bool ledState; // ledState used to set the LED
unsigned long previousMillis; // will store last time LED was updated
int fadeValue;
long interval;

public: 
MyWs2812(int index,int interval){
  this->index = index;
  this->ledState = false;
  this->interval = interval;
  this->previousMillis = 0;
  this->fadeValue = 0;

}  
  void setPreviousMillis(unsigned long millis){
    previousMillis = millis;
  }
  unsigned long getPreviousMillis(){
    return previousMillis;
  }

  void Update(int newInterval){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > newInterval) {
      previousMillis = currentMillis; // save the last time you blinked the LED 
      if(ledState == false){
          fadeValue = fadeValue + 20;
        if (fadeValue >= 255) {// At max, limit and change direction
          fadeValue = 255;
          ledState = true;
        }
      }else{
          fadeValue = fadeValue - 20;
          if (fadeValue <= 0) {
            // At min, limit and change direction
            fadeValue = 0;
            ledState = false;
          }
      }
        strip.setPixelColor(index, strip.Color(0, 0, fadeValue));        
        strip.show();   
    }
  }

};

MyWs2812 led0(0,200);
int previousVolumeState = 0;

void loop() {
  // unsigned long currentMillis = millis();
// if(currentMillis>=4000 &&currentMillis<=21000){
//   if(currentMillis - previousMillis1 > OnTime1) {
//       previousMillis1 = currentMillis; // save the last time you blinked the LED 
//       if(ledState1 == false){
//         strip.setPixelColor(10, strip.Color(255, 0, 0));//red
//         strip.show();
//         ledState1 = true;
//       }else{
//         strip.setPixelColor(10, strip.Color(255, 255, 255));//yellow
//         strip.show();  
//         ledState1 = false;
//       } 
//     }
// }
  initialization(millis());
  // myDFPlayer.volume(map(analogRead(A0),0,1023,0,27));
  // int newVolume = (int) 28 * analogRead(A0) / 1024;

  if( millis()-previousVolumeState > 500 ){
     previousVolumeState = millis();
     if( ((int) 27 * analogRead(A0) / 1024) != currentVolume){
       currentVolume = myDFPlayer.readVolume();
        myDFPlayer.volume(((int) 27 * analogRead(A0) / 1024));
        Serial.print("changed volume");
        Serial.println(currentVolume);
     }
  }
  // if( ((int) 28 * analogRead(A0) / 1024) != myDFPlayer.readVolume() ){
  //   myDFPlayer.volume(((int) 28 * analogRead(A0) / 1024));
  // }

  //  if (myDFPlayer.available()) {
  //   printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  // }
// led5.Update(200);`
// led2.Update();

//now it  worked! wrong stateMachine before
  // if( (millis()-previousMillis) > 500){
  //     previousMillis = millis();
  //     strip.setPixelColor(i, strip.Color(0, 0, 255));        
  //     strip.show(); 
  //     i++; 
  // }                    

  // fadeInOut();

  // Fill along the length of the strip in various colors...
  // colorWipe(strip.Color(255, 0, 0), 200); // Red
  // colorWipe(strip.Color(  0, 255,   0), 500); // Green
  // colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  // theaterChase(strip.Color(127, 127, 127), 500); // White, half brightness
  // theaterChase(strip.Color(127,   0,   0), 500); // Red, half brightness
  // theaterChase(strip.Color(  0,   0, 127), 500); // Blue, half brightness

  // rainbow(500);             // Flowing rainbow cycle along the whole strip
  // theaterChaseRainbow(500); // Rainbow-enhanced theaterChase variant

  // colorFade(255, 0, 0, 300); // fade into red
  // colorFade(0, 0, 150, 300); // and then into white

}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}

