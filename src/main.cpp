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
#define LED_COUNT 39 //66
#define Gate 9
int Sound_Pin=A0;//A0/6
int threshold=1;


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySoftwareSerial(2, 3); // RX(10), TX(11) || 2,3
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


  unsigned long previousStarFadeMillis = 0;
  bool starState = false;
  int boxLayer3[12] = {24,25,26,27,28,29,30,31,32,33,34,35}; 
  int boxLayer2[12] = {12,13,14,15,16,17,18,19,20,21,22,23};
  int boxLayer1[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
  int boxLayerCount = 3;
  int boxHeart3[9] = {54,55,56,57,58,59,60,61,62};//54,55,56,57,58,59,60,61,62
  int boxHeart2[9] = {33,34,35,36,37,38,39,40,41};//33,34,35,36,37,38,39,40,41
  int boxHeart1[9] = {12,13,14,15,16,17,18,19,20};//12,13,14,15,16,17,18,19,20
  int boxHeartCount = 3;
  int allCorner[36] = {0,1,2,3,4,5,6,7,8,9,10,11,
                      12,13,14,15,16,17,18,19,20,21,22,23,
                      24,25,26,27,28,29,30,31,32,33,34,35};


int allHeart[27] ={12,13,14,15,16,17,18,19,20,
                  33,34,35,36,37,38,39,40,41,
                  54,55,56,57,58,59,60,61,62};
int color = 50;
int rainDropC3 = 40;
int rainDropC2 = 40;
int rainDropC1 = 40;
unsigned long rainDropC3Previous=0;
unsigned long rainDropC2Previous=0;
unsigned long rainDropC1Previous=0;
bool thirdState = false;
bool secondState = false;
bool firstState = false;
bool rainDownState = false;
void fadeUsingCosine(unsigned long currentMillis){ //glow the Star*
  // if( (currentMillis >= 12900) && currentMillis<=20000 ){ 
  //     color = 128+127*cos(2*PI/1000*currentMillis);  //fadeUsingCosine
  //     strip.setPixelColor(10, strip.Color(color, color,0 ));// sets the value (range from 0 to 255) 
  //     strip.show();
  // }

 if( (currentMillis >= 12700) && currentMillis<=20000 ){
  // if( (currentMillis >= 13000 && currentMillis <= 14000) || (currentMillis >= 16000 && currentMillis <= 17000)){ // if 13000, show rainDownCircle

    if( currentMillis >= 13000 && currentMillis <= 15000){ //glow thirdLayer
      if( currentMillis-rainDropC3Previous > 15){
        rainDropC3Previous=currentMillis;
        if(thirdState==false){ //turn on
          rainDropC3+=10;
            for(int i=0; i<=11; i++){
              strip.setPixelColor(boxLayer3[i], strip.Color(rainDropC3, rainDropC3, 0));
            }
              strip.show();
          if(rainDropC3>=245 )
            thirdState=true;
        }else{ //turn off
            if(rainDropC3 >=40){ //43 already black color
              rainDropC3-=10;
              for(int i=0; i<=11; i++){
                strip.setPixelColor(boxLayer3[i], strip.Color(rainDropC3, rainDropC3, 0));
              }
                strip.show();
            }
        }
      }
    }
    if( currentMillis >= 13500 && currentMillis <= 15500){ //glow secondLayer
      if( currentMillis-rainDropC2Previous > 15){
        rainDropC2Previous=currentMillis;
        if(secondState==false){ //turn on
          rainDropC2+=5;
            for(int i=0; i<=11; i++){
              strip.setPixelColor(boxLayer2[i], strip.Color(rainDropC2, rainDropC2, 0));
            }
              strip.show();
          if(rainDropC2>=245 )
            secondState=true;
        }else{ //turn off
            if(rainDropC2 >=40){ //43 already black color
              rainDropC2-=5;
              for(int i=0; i<=11; i++){
                strip.setPixelColor(boxLayer2[i], strip.Color(rainDropC2, rainDropC2, 0));
              }
                strip.show();
            }
        }
      }
    }
    if( currentMillis >= 14000 && currentMillis <= 16000){ //glow firstLayer
      if( currentMillis-rainDropC1Previous > 15){
        rainDropC1Previous=currentMillis;
        if(firstState==false){ //turn on
          rainDropC1+=5;
            for(int i=0; i<=11; i++){
              strip.setPixelColor(boxLayer1[i], strip.Color(rainDropC1, rainDropC1, 0));
            }
              strip.show();
          if(rainDropC1>=245 )
            firstState=true;
        }else{ //turn off
            if(rainDropC1 >=40){ //43 already black color
              rainDropC1-=10;
              for(int i=0; i<=11; i++){
                strip.setPixelColor(boxLayer1[i], strip.Color(rainDropC1, rainDropC1, 0));
              }
                strip.show();
            }
        }
      }
    }


  if( (millis()-previousStarFadeMillis) > 40){ //and glow the Star*
      previousStarFadeMillis = millis();
      if(starState==false){
        color+=10;        
        strip.setPixelColor(strip.numPixels()-1, strip.Color(color, color, 0));        
        strip.setPixelColor(strip.numPixels()-2, strip.Color(color, color, 0));        
        strip.setPixelColor(strip.numPixels()-3, strip.Color(color, color, 0));        
        strip.show(); 
        if(color>=255){
          starState=true;
        }
      }
      if(starState==true){
        color-=10;        
        strip.setPixelColor(strip.numPixels()-1, strip.Color(color, color, 0));        
        strip.setPixelColor(strip.numPixels()-2, strip.Color(color, color, 0));        
        strip.setPixelColor(strip.numPixels()-3, strip.Color(color, color, 0));        
        strip.show(); 
        if(color<=55){
          starState=false;
        }
      }
  }
 }
}

unsigned long previousBlowMillis = 0;
unsigned long previousRandomSparkle = 0;
unsigned long previousRadomDelay = 0;
int blowColor = 50;
bool glowChange = false;
bool blowState = false;
void blowHearts(unsigned long currentMillis){
  if(currentMillis == 21000 || currentMillis == 25000 || currentMillis == 29000){ //restart variables every: 21000, 25000 and 29000
      glowChange=false;
      blowState=false;
      blowColor=50;
    }
      
  if( currentMillis >= 17000 && currentMillis <= 31000){ //random sparkle //19800-31000
    if((millis()-previousRandomSparkle) > 100){//150
      previousRandomSparkle = millis();
      int rand = random(0,36);
      strip.setPixelColor(allCorner[rand],255, 255, 255);
      strip.show();
      if((millis()-previousRadomDelay) > 100){//150
        previousRadomDelay = millis();
        strip.setPixelColor(allCorner[rand],0,0,0);
        strip.show();
      }
    }
  }

  if( (currentMillis >= 19700 && currentMillis <= 21000) || //19800-21000
      (currentMillis >= 23100 && currentMillis <= 24300) || //23300-24300
      (currentMillis >= 26700 && currentMillis <= 28000) || //27000-28000
      (currentMillis >= 30200 && currentMillis <= 31500) ){ 

    if( (millis()-previousBlowMillis) > 15){ //glow from white to red
        previousBlowMillis = millis();
        if(blowState==false){
          blowColor+=10;      
          if(glowChange && blowColor <=255){ //glow red heart
            for(int i=0; i<=8; i++){ 
              if(boxHeartCount==2){
                strip.setPixelColor(boxLayer3[i], strip.Color(blowColor, blowColor, 0));
              }else if(boxHeartCount==1){
                strip.setPixelColor(boxLayer2[i], strip.Color(blowColor, blowColor, 0));
              }else if(boxHeartCount==0){
                strip.setPixelColor(boxLayer1[i], strip.Color(blowColor, blowColor, 0));
              }else if(boxHeartCount==-1){ //glow all 3 red hearts
                strip.setPixelColor(boxLayer3[i], strip.Color(blowColor, blowColor, 0));
                strip.setPixelColor(boxLayer2[i], strip.Color(blowColor, blowColor, 0));
                strip.setPixelColor(boxLayer1[i], strip.Color(blowColor, blowColor, 0));
              }
            }
            // strip.setPixelColor(5, strip.Color(blowColor,0, 0));//red 
          }else if(glowChange==false){ //glow white heart
            for(int i=0; i<=8; i++){ 
              if(boxHeartCount==3){
                strip.setPixelColor(boxLayer3[i], strip.Color(blowColor, blowColor, blowColor));
              }else if(boxHeartCount==2){
                strip.setPixelColor(boxLayer2[i], strip.Color(blowColor, blowColor, blowColor));
                strip.setPixelColor(boxLayer3[i], strip.Color(0, 0, 0));
              }else if(boxHeartCount==1){
                strip.setPixelColor(boxLayer1[i], strip.Color(blowColor, blowColor, blowColor));
                strip.setPixelColor(boxLayer2[i], strip.Color(0, 0, 0));
              }else if(boxHeartCount==0){
                strip.setPixelColor(boxLayer3[i], strip.Color(blowColor, blowColor, blowColor));
                strip.setPixelColor(boxLayer2[i], strip.Color(blowColor, blowColor, blowColor));
                strip.setPixelColor(boxLayer1[i], strip.Color(blowColor, blowColor, blowColor));
              }
            }
            // strip.setPixelColor(5, strip.Color(blowColor, blowColor, blowColor));//white
          }
          strip.show(); 
          if(blowColor>=255 && glowChange ==false){
            blowState=true;
          }
        }
        if(blowState==true){//decrease white
          blowColor-=10;
            for(int i=0; i<=8; i++){ 
              if(boxHeartCount==3){
                strip.setPixelColor(boxLayer3[i], strip.Color(blowColor, blowColor, blowColor));
              }else if(boxHeartCount==2){
                strip.setPixelColor(boxLayer2[i], strip.Color(blowColor, blowColor, blowColor));
              }else if(boxHeartCount==1){
                strip.setPixelColor(boxLayer1[i], strip.Color(blowColor, blowColor, blowColor));
              }else if(boxHeartCount==0){
                strip.setPixelColor(boxLayer3[i], strip.Color(blowColor, blowColor, blowColor));
                strip.setPixelColor(boxLayer2[i], strip.Color(blowColor, blowColor, blowColor));
                strip.setPixelColor(boxLayer1[i], strip.Color(blowColor, blowColor, blowColor));
              }
            }
            // strip.setPixelColor(5, strip.Color(blowColor, blowColor, blowColor)); 
            strip.show(); 
          if(blowColor<=55){
            blowState=false;
            glowChange=true;
            boxHeartCount--;
          }
        }
    }
  }
}

int previousMillis = 0;
int i = 0;
bool indexState = false;
int indexColor = 30;
void initialization(unsigned long currentMillis){
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t yellow = strip.Color(255, 255, 0);
  // Serial.println(currentMillis);
 
  if( (currentMillis == 3500) ){ // delay(1000);
  Serial.print("milli 1000!!!:");
  Serial.println(millis());
  strip.setPixelColor(0, white);
  strip.show();
  }
  if(millis() >= 5000){ //delay(4000);
    if( ( currentMillis-previousMillis > 210) && i<=strip.numPixels()-3){
        previousMillis = currentMillis;
        if(i != strip.numPixels()-3)
          strip.setPixelColor(i, white);
        strip.show();
        strip.setPixelColor(i-1, strip.Color(0, 0, 0));
        strip.show();
        i++;
        Serial.println(i);
      }
  }
}

bool ledState1 = false;             // ledState used to set the LED
unsigned long previousMillis1 = 0;        // will store last time LED was updated
long OnTime1 = 1000;           // milliseconds of on-time
long OffTime1 = 1000; 
int currentVolume = 0;
void setup() {
  Serial.begin(115200);//115200
  mySoftwareSerial.begin(9600);
  pinMode(Gate,OUTPUT);//fan gate
  pinMode(Sound_Pin,INPUT); //sound sensor
  digitalWrite(Gate,LOW); //turn off fan first
  // pinMode(A0, INPUT);//volume potentiometer

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
    strip.clear();
    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    Serial.println(F("DFPlayer Mini online."));
    // currentVolume = map(analogRead(A0),0,1023,0,27);
    myDFPlayer.volume(10);//18 || 25,27
    // myDFPlayer.play(); //(1)play music
    myDFPlayer.enableLoopAll(); //loop all mp3 files.
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
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 768) {//256,512,
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
        // delay(wait);  // add a delay if its too fast
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
void fadeToBlack(int ledNo, byte fadeValue) {
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);
    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    strip.setPixelColor(ledNo, r,g,b);
}

unsigned long previousFadeAllMilli = 0;
void fadeAllToBlack(unsigned long currentMillis,int delay){//int delayTime
  // for(int j=0; j<(LED_COUNT); j++) { 
    if( (currentMillis-previousFadeAllMilli) > 2){
        previousFadeAllMilli = currentMillis;
      if( (random(10)>5) ) {
        fadeToBlack(random(LED_COUNT), delay );  
        strip.show();    
        // delay(delayTime);
      }
    }
    // }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  for(int i = (LED_COUNT-3)+(LED_COUNT-3); i > 0 ; i--) {// fade brightness all LEDs one step
    for(int j=0; j<(LED_COUNT-3); j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    for(int j = 0; j < meteorSize; j++) {// draw meteor
      if( ( i-j <(LED_COUNT-3)) && (i-j>=0) ) {
        strip.setPixelColor(i-j, red, green, blue);
        
      }
    }
    strip.show();
    delay(SpeedDelay);
  }
}

void meteorRainUp(byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  for(int i = 0; i <(LED_COUNT-3)+(LED_COUNT-3) ; i++) {// fade brightness all LEDs one step
    for(int j=0; j<(LED_COUNT-3); j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    for(int j = 0; j < meteorSize; j++) {// draw meteor
      if( ( i-j <(LED_COUNT-3)) && (i-j>=0) ) {
        strip.setPixelColor(i-j, 222, 33, 212);
        
      }
    }
    strip.show();
    delay(SpeedDelay);
  }
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  for (int i=0; i<20; i++) {
      strip.setPixelColor(random(LED_COUNT-3),random(0,255),random(0,255),random(0,255));
     strip.show();
     if(OnlyOne)
     strip.clear();
   }
  delay(SpeedDelay);
}

unsigned long previousSparkleMilli= 0;
void SparkleCorners(){ //white sparkle
  if((millis()-previousSparkleMilli) > 100){
    previousSparkleMilli = millis();
    int rand = random(0,36);
    strip.setPixelColor(allCorner[rand],random(255), random(255), random(255));
    strip.show();
  }
}

unsigned long previousSparkleHeartMilli= 0;
void SparkleHeart(){ //white sparkle
  if((millis()-previousSparkleHeartMilli) > 100){
    previousSparkleHeartMilli = millis();
    int rand = random(0,27);
    strip.setPixelColor(allHeart[rand],255, 0, 0);
    strip.show();
  }
}

void SnowSparkle(int SparkleDelay, int SpeedDelay) {
  int Pixel = random(LED_COUNT-3);
  strip.setPixelColor(Pixel,0xff,0xff,0xff);
  strip.show();
  delay(SparkleDelay);
  strip.setPixelColor(Pixel,255,255,255);
  strip.show();
  delay(SpeedDelay);

}

void SnowSparkleMultiple(int SpeedDelay){
  for (int i=0; i<10; i++) {
    strip.setPixelColor(random(LED_COUNT-3),random(255),random(255),random(255));
    strip.show();
   }
    delay(random(10,100));
  strip.clear();
  strip.show();
  delay(SpeedDelay);
}

unsigned long previousColorWipe = 0;
void colorWipe(unsigned long currentMillis) { //byte r, byte g, byte b
   int r = random(255);
   int g = random(255);
   int b = random(255);
    if((currentMillis-previousColorWipe) > 850){
      previousColorWipe = currentMillis;
      for(uint16_t i=0; i<LED_COUNT-3; i++) {
        strip.setPixelColor(i, r, g, b);
        strip.show();
        delay(3);
      }
    }
}

unsigned long previousmultiColorWipe = 0;
void multiColorWipe(unsigned long currentMillis) {
  if((currentMillis-previousmultiColorWipe) > 500){
    previousmultiColorWipe = currentMillis;
    for(int i=0; i<LED_COUNT-3; i++) { 
      strip.setPixelColor(i, random(255),random(255),random(255));        
      // delay(1);
    }
      strip.show();
  }
}

void yellowDotGoesToStar(){
  for(int i=0; i<=LED_COUNT-1;i++){
    strip.setPixelColor(i, strip.Color(255, 255, 0));
    strip.show();
    delay(15);
    strip.setPixelColor(i-1, strip.Color(0, 0, 0));
    strip.show();
    delay(15);
    if(i==LED_COUNT-1){
      strip.setPixelColor(i, strip.Color(255, 255, 0));
      strip.show();
    }
  }
}

void meteorRainUpFinal(byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  for(int i = 0; i <(36)+(36) ; i++) {// fade brightness all LEDs one step
    for(int j=0; j<(36); j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(allCorner[j], meteorTrailDecay );        
      }
    }
    for(int j = 0; j < meteorSize; j++) {// draw meteor
      if( ( i-j <(36)) && (i-j>=0) ) {
        strip.setPixelColor(allCorner[i-j], 255, 255, 255);
        
      }
    }
    strip.show();
    delay(SpeedDelay);
  }
}

int starColor = 50;
void glowStar(unsigned long currentMillis){
  if( (millis()-previousStarFadeMillis) > 10){ //glow the Star*
      previousStarFadeMillis = millis();
      if(starState==false){
        starColor+=10;        
        strip.setPixelColor(strip.numPixels()-1, strip.Color(starColor, starColor, starColor));        
        strip.setPixelColor(strip.numPixels()-2, strip.Color(starColor, starColor, starColor));        
        strip.setPixelColor(strip.numPixels()-3, strip.Color(starColor, starColor, starColor));        
        strip.show(); 
        if(starColor>=255){
          starState=true;
        }
      }
      if(starState==true){
        starColor-=10;        
        strip.setPixelColor(strip.numPixels()-1, strip.Color(starColor, starColor, starColor));        
        strip.setPixelColor(strip.numPixels()-2, strip.Color(starColor, starColor, starColor));        
        strip.setPixelColor(strip.numPixels()-3, strip.Color(starColor, starColor, starColor));        
        strip.show(); 
        if(starColor<=55){
          starState=false;
        }
      }
  }
}

void loop() {
  unsigned long currentMillis = millis();

  initialization(millis());
  fadeUsingCosine(millis());
  blowHearts(millis());
  if(currentMillis >= 31500 && currentMillis <= 32850) 
    meteorRain(255,255,0,8, 10, true, 10); //r,g,b,meteorSize, byte meteorTrailDecay,bool, delay
  if(currentMillis >= 33000 && currentMillis <= 52500){
    colorWipe(millis());
    if(currentMillis >= 33000 && currentMillis <= 40000)//33000-43000 open the gate for 7 seconds
      digitalWrite(Gate,HIGH);
    if(currentMillis >= 40000)//38000 close the gate
      digitalWrite(Gate,LOW);
  }
  if(currentMillis>=53500 && currentMillis<=59500)
    fadeAllToBlack(millis(),50);
  if(currentMillis>=63000 && currentMillis<=69000)//60000-66000
     SnowSparkleMultiple(random(10,400));
  if(currentMillis>=69000 && currentMillis<=70000) //  6600-67000
    meteorRainUp(15, 15, true, 25);//20
  if(currentMillis>=72200 && currentMillis<=81500 || currentMillis>=97000){ //68200-77500 || 93000 light the star
    strip.setPixelColor(LED_COUNT-1, strip.Color(255, 255, 0));
    strip.setPixelColor(LED_COUNT-2, strip.Color(255, 255, 0));
    strip.setPixelColor(LED_COUNT-3, strip.Color(255, 255, 0));
    strip.show();
  }
  if(currentMillis>=73800 && currentMillis<=85300)//70300-77000 //multiColorWipe
    multiColorWipe(millis());
  if(currentMillis>=85300 && currentMillis<=87700) //77400-80000 clear all
    strip.clear();
  if(currentMillis>=87700 && currentMillis<=89000)//80500-82000
    meteorRainUpFinal(10, 5, true, 40);
  if(currentMillis>=89000 && currentMillis<=98000){//82000-90000
    glowStar(millis());
    SparkleCorners();
    // SparkleHeart();
  }
///Sound Sensor reactive to music////
    Serial.println(analogRead(Sound_Pin));
  if(currentMillis>=98000){//93000
    if(analogRead(Sound_Pin) >= 525){//515 || 525    analogRead(Sound_Pin) >= 515
        strip.fill(strip.Color(random(255),random(255),random(255)),0,36);
        strip.show();
    }else{
        strip.clear();
        strip.show();
    }
  }


  // Volume Controll
  // if( millis()-previousVolumeState > 1000 ){
  //    previousVolumeState = millis();
  //    if( ((int) 27 * analogRead(A0) / 1024) != currentVolume){
  //      myDFPlayer.volume(map(analogRead(A0),0,1023,0,27));
  //       myDFPlayer.volume(((int) 27 * analogRead(A0) / 1024));
  //       currentVolume = myDFPlayer.readVolume();
  //       Serial.print("changed volume:");
  //       Serial.println(myDFPlayer.readVolume());
  //    }
  // }
  
  // if( ((int) 28 * analogRead(A0) / 1024) != myDFPlayer.readVolume() ){
  //   myDFPlayer.volume(((int) 28 * analogRead(A0) / 1024));
  // }

  //  if (myDFPlayer.available()) {
  //   printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  // }

//now it  worked! wrong stateMachine before
  // if( (millis()-previousMillis) > 500){
  //     previousMillis = millis();
  //     strip.setPixelColor(i, strip.Color(0, 0, 255));        
  //     strip.show(); 
  //     i++; 
  // }                    

  // fadeInOut();
  // Do a theater marquee effect in various colors...
  // theaterChase(strip.Color(127, 127, 127), 500); // White, half brightness
  // theaterChase(strip.Color(127,   0,   0), 500); // Red, half brightness
  // theaterChase(strip.Color(  0,   0, 127), 500); // Blue, half brightness

  // rainbow(50);             // Flowing rainbow cycle along the whole strip
  // theaterChaseRainbow(500); // Rainbow-enhanced theaterChase variant

  // colorFade(255, 0, 0, 20); // fade into red
  // colorFade(0, 255, 0, 2); // fade into red
  // colorFade(150, 150, 150, 300); // and then into white

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

